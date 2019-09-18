#include "pwm.h"
#include "defines.h"
#include <avr/io.h>


void pwm_init() {
    DDRB |= (1 << PB0);     // Set pin as output
    OCR0 = 0xFF;

    TCCR0 |= (1 << FOC0);
    TCCR0 |= (1 << WGM01);  // Set in CTC mode
    TCCR0 |= (1 << COM01);  // Set OC0 to toggle
    TCCR0 |= (1 << CS00);   // Set prescaler = 1

}


void pwm_set_freq(int freq) {


}


void pwm_start() {


}


void pwm_stop() {


}