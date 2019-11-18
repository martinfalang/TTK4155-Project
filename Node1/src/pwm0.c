#include "../../lib/inc/defines.h"
#include "pwm0.h"

#include <stdio.h>


#define DEBUG 0

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
    if (freq == 0) {  // turn off pwm signal
        prescaler = 0;
        pwm0_set_prescaler(PREOFF);
        return;
    }

    // search for best prescaler
    // taken a lot of inspiration from arduino's `tone` function
    int ocr = F_CPU / freq / 2;
    prescaler = 1;

    if (ocr > 255 + 1) {
        prescaler = 8;
        ocr = ocr / 8;  // try next prescaler

        if (ocr > 255 + 1) {
            prescaler = 64;
            ocr = ocr / 8;  // 1 / 8 / 8 = 1 / 64

            if (ocr > 255 + 1) {
                prescaler = 256;
                ocr = ocr / 4;
                
                if (ocr > 255 + 1) {
                    prescaler = 1024;
                    ocr = ocr / 4;
                }
            }
        }
    }

#if DEBUG
    printf("pwm0_set_freq: prescaler = %d\n", prescaler);
#endif

    // we need to subtract one to get the correct OCR0 value, but by doing it
    // last, after selecting the correct prescaler, we can do less calculations
    // and hopefully don't use too much resources on calculating this. 
    ocr = ocr - 1;
    OCR0 = ocr;
    
    switch (prescaler)
    {
    case 1:
        pwm0_set_prescaler(PRE1);
        break;
    case 8:
        pwm0_set_prescaler(PRE8);
        break;
    case 64:
        pwm0_set_prescaler(PRE64);
        break;
    case 256:
        pwm0_set_prescaler(PRE256);
        break;
    case 1024:
        pwm0_set_prescaler(PRE1024);
        break;
    default:
        break;
    }
}


void pwm0_set_prescaler(pwm0_prescaler_t ps) {
    // Set all prescaler bits to zero
    TCCR0 = TCCR0 & PREOFF;

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

#if DEBUG
    printf("pwm0_set_prescaler: %d\n", prescaler); 
#endif

    // By not setting all prescaler bits to 0, the PWM is turned off
    TCCR0 = TCCR0 | ps;
}


uint16_t pwm0_get_prescaler() {
    return prescaler;
}


void pwm0_stop() {
    TCCR0 = 0;
}
