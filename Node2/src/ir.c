
////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////

#include "ir.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdio.h>

////////////////////////////////////////////////////////////////////////////////
// Defines
////////////////////////////////////////////////////////////////////////////////

#define ADC_THRESHOLD               200
#define ADC_CONSECUTIVE_THRESHOLD   3

////////////////////////////////////////////////////////////////////////////////
// Private variables
////////////////////////////////////////////////////////////////////////////////

static volatile bool conversion_complete = false;
static bool beam_broken = false;
static uint8_t num_samples = 0;

////////////////////////////////////////////////////////////////////////////////
// Public functions
////////////////////////////////////////////////////////////////////////////////

void ir_init(void) {

    // Set PF0 to input
    DDRF &= ~(1 << PF0);

    // Set Vref = AVcc
    ADMUX |= (1 << REFS0);

    // Enable ADC
    ADCSRA |= (1 << ADEN);

    // Enable global interrupts
    sei();

    // Enable ADC conversion complete interrupt
    ADCSRA |= (1 << ADIE);
}

void _start_conversion(void) {
    ADCSRA |= (1 << ADSC);
}

ISR(ADC_vect) {
    conversion_complete = true;
}

/*
    Checks if the IR-beam has been broken.
    Must record 3 consecutive broken beams 
    in order to return false
*/
bool ir_beam_broken(void) {
    if (!beam_broken && conversion_complete) {

        conversion_complete = false;

        if (ADC <= ADC_THRESHOLD        ) {
            if (++num_samples >= ADC_CONSECUTIVE_THRESHOLD) {
                beam_broken = true;
            }
        }
        else {
            num_samples = 0;
        }
    }
    else if (!beam_broken) {
        _start_conversion();
    }
    
    return beam_broken;
}


void ir_reset(void) {
    beam_broken = false;
    num_samples = 0;
    conversion_complete = false;
}

#if DEBUG
void ir_test(void) {
    if (!beam_broken) {
        uint8_t broken_beam = ir_beam_broken();
        printf("Beam broken: %i\n", broken_beam);
    }
}
#endif // DEBUG