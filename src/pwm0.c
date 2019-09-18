#include "pwm0.h"
#include "defines.h"

static uint16_t prescaler = 0;

void pwm0_init(pwm0_prescaler_t ps) {
    DDRB |= (1 << PB0);     // Set pin as output
    OCR0 = 0xFF;

    TCCR0 |= (1 << FOC0);
    TCCR0 |= (1 << WGM01);  // Set in CTC mode
    TCCR0 |= (1 << COM00);  // Set OC0 to clear on match
    pwm0_set_prescaler(ps);
}


void pwm0_set_freq(uint16_t freq) {
    if (prescaler == 0) return;  // clock stopped

    int new_oc0 = F_CPU / freq / (2 * prescaler) - 1;
    OCR0 = new_oc0 & 0xFF;
}


void pwm0_set_prescaler(pwm0_prescaler_t ps) {
    // Set all prescaler bits to zero
    TCCR0 &= ~( (1 << CS00) | (1 << CS01) | (1 << CS02) );

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

    // By not setting a prescaler (i.e. to 0) the PWM is turned off
    if (prescaler != 0) {
        TCCR0 |= ps;
    }
}


uint16_t pwm0_get_prescaler() {
    return prescaler;
}