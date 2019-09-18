#include "pwm.h"
#include "defines.h"
#include <avr/io.h>

#define PRESCALER 64

void pwm_init() {
    DDRB |= (1 << PB0);     // Set pin as output
    OCR0 = 0xFF;

    TCCR0 |= (1 << FOC0);
    TCCR0 |= (1 << WGM01);  // Set in CTC mode
    TCCR0 |= (1 << COM00);  // Set OC0 to clear on match
    TCCR0 |= (1 << CS01) | (1 << CS00);   // Set prescaler = 64
}


void pwm_set_freq(int freq) {
    // TODO: make prescaler change based on frequency range
    int new_oc0 = F_CPU / freq / (2*PRESCALER) - 1;
    OCR0 = new_oc0 & 0xFF;
}