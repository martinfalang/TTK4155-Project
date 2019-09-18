#include "pwm0.h"
#include "defines.h"

static uint16_t prescaler = 256;

void pwm0_init() {
    DDRB |= (1 << PB0);     // Set pin as output
    OCR0 = 0xFF;

    TCCR0 |= (1 << FOC0);
    TCCR0 |= (1 << WGM01);  // Set in CTC mode
    TCCR0 |= (1 << COM00);  // Set OC0 to clear on match
    TCCR0 |= (1 << CS02);   // prescaler = 256
}


void pwm0_set_freq(uint16_t freq) {
    if (prescaler == 0) return;  // clock stopped

    int new_oc0 = F_CPU / freq / (2 * prescaler) - 1;
    OCR0 = new_oc0;
}


void pwm0_set_prescaler(pwm0_prescaler_t ps) {
    // Set all prescaler bits to zero
    TCCR0 &= PREOFF;

    switch (ps) {
        case PREOFF:
            prescaler = 0;
            break;
        case PRE1:
            prescaler = 1;
            break;
        case PRE8:
            prescaler = 8;
            break;
        case PRE64:
            prescaler = 64;
            break;
        case PRE256:
            prescaler = 256;
            break;
        case PRE1024:
            prescaler = 1024;
            break;
        default:
            break;
    }
    
    // By not setting all prescaler bits to 0, the PWM is turned off
    TCCR0 |= ps;
}


uint16_t pwm0_get_prescaler() {
    return prescaler;
}
