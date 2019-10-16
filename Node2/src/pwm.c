// Module for controlling the servo through PWM

// Period 20ms
// Duty cycle * Period in interval [0.9, 2.1] ms


#include <avr/io.h>

// Definitions
// We use PB7 as our pwm pin (OC0A-pin)
// See docs/schematics/arduino-mega2560_r3-sch.pdf for schematics
#define PWM_PIN PD0

// Initialize pwm in fast_pwm-mode
void pwm_init(void) {
    // Set PWM pin as output
    DDRD |= (1 << PWM_PIN);

    // Set TIMER0 to fast pwm mode (mode 7)
    TCCR0A |= (1 << WGM00) | (1 << WGM01);
    TCCR0B |= (1 << WGM02); // For some reason in the other register

    // Set OC0B to non-inverting mode (see Table 16-6 p. 126)
    TCCR0B |= (1 << COM0B1);
    TCCR0B &= ~(1 << COM0B0); 

    // The timer/counter module has two independent 
    // sources for pwm generation. We use A.
    OCR0B = 60; // TODO: Find the right value (most likely not 60)

}
