// Module for controlling the servo through PWM

// Period 20ms
// Duty cycle * Period in interval [0.9, 2.1] ms


#include <avr/io.h>

// Definitions
// See docs/schematics/arduino-mega2560_r3-sch.pdf for schematics
#define PWM_PIN PG5 // OC0B

// General idea: Set one OCR such that we can reset the timer from the interrupt, set the
// other to generate the PWM signal.

void pwm_set_duty_cycle(uint8_t ms_tenths) {
    // Allows to set the duty_cycle to somewhere between 9 and 21 tenths of a milisecond
    if (9 <= ms_tenths && ms_tenths <= 20) {
        // Set duty cycle by updating OCR
    }
}

// Initialize pwm in fast_pwm-mode
void pwm_init(void) {
    // Set PWM pin as output
    DDRG |= (1 << PWM_PIN);

    // Set TIMER0 to fast pwm mode (mode 7)
    TCCR0A |= (1 << WGM00) | (1 << WGM01);
    TCCR0B |= (1 << WGM02); // For some reason in the other register

    // Set OC0B to non-inverting mode (see Table 16-6 p. 126)
    
    TCCR0B |= (1 << COM0A1);
    TCCR0B &= ~(1 << COM0A0); 

    // TODO:
    // Set the timer to the greatest

}
