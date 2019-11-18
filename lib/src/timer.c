
/*
    This module handles the timing of the Atmega162 and ATmega2560. It makes it 
    possible only do operations at a specified frequency without using delays. 
    The 60Hz timer is the main timer and is the refresh rate of the OLED screen. 
    The other timers are derived from this timer.
*/

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////

#include "../inc/timer.h"
#include "../inc/defines.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

////////////////////////////////////////////////////////////////////////////////
// Private variables
////////////////////////////////////////////////////////////////////////////////

static bool _60Hz_timeout = false;
static unsigned char _1Hz_counter = 0;
static unsigned char _6Hz_counter = 0;
static unsigned char _10Hz_counter = 0;        

////////////////////////////////////////////////////////////////////////////////
// Public functions
////////////////////////////////////////////////////////////////////////////////

void timer_init(void) {

    // Node 1 timer
#if defined (__AVR_ATmega162__)

    // Initializes a timer that raises an interrupt 
    // setting a flag telling if the screen should be updated

    // Set Force Output Compare high
    TCCR2 |= (1 << FOC2);

    // Set Clear-to-Clear mode for clock 2
    TCCR2 |= (1 << WGM21);
    TCCR2 &= ~(1 << WGM20);

    // Set the register to clear on match
    TCCR2 |= (1 << COM21);
    TCCR2 &= ~(1 << COM20);

    // Set clock prescaler to CLT_T2_S/1024
    TCCR2 |= (1 << CS20) | (1 << CS21) | (1 << CS22);

    // Set the timer counter register to 0
    TCNT2 = 0; 

    // Set output compare register to 80, which should amount to 
    // interrupts about 60 times per second
    OCR2 = 80;

    // Activate Timer2 Output Compare in interrupt mask
    TIMSK |= (1 << OCIE2);

    // Enable interrupts globally
    sei();

#elif defined (__AVR_ATmega2560__)
    // Setup timer 3
    // CTC mode with TOP = OCR3A, disconnected pin
    TCCR3B |= (1 << WGM02);
    TCCR3A = 0;

    // Set for 60 Hz
    uint32_t ocr = (uint32_t)F_CPU * 0.033 / (2UL * 64UL);
    OCR3A = (uint16_t)ocr;

    TIMSK3 |= (1 << OCIE3A);
    sei();

    // Start timer
    TCCR3B |= (1 << CS31) | (1 << CS30);

#endif
}

bool timer_get_60Hz_timeout(void) {
    if (_60Hz_timeout) {
        _60Hz_timeout = false;
        return true;
    }
    return false;
}

bool timer_get_1Hz_timeout(void) {
    if (_1Hz_counter >= _1HZ_COUNT) {
        _1Hz_counter = 0;
        return true;
    }
    return false;
}

bool timer_get_6Hz_timeout(void) {
    if (_6Hz_counter >= _6HZ_COUNT) {
        _6Hz_counter = 0;
        return true;
    }
    return false;
}

bool timer_get_10Hz_timeout(void) {

    if (_10Hz_counter >= _10HZ_COUNT) {
        _10Hz_counter = 0;
        return true;
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////
// Interrupt service routine
////////////////////////////////////////////////////////////////////////////////

ISR(TIMER_ISR_VECT) {
    _60Hz_timeout = true;
    _10Hz_counter++;
    _1Hz_counter++;
    _6Hz_counter++;
}