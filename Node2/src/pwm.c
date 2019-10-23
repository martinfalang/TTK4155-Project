// Module for controlling the servo through PWM

// Period 20ms
// Duty cycle * Period in interval [0.9, 2.1] ms


#include <avr/io.h>

// Definitions
// See docs/schematics/arduino-mega2560_r3-sch.pdf for schematics
#define PWM_PIN PB5 // OC1A

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
    // Set PWM pin as output. Use OC1A - PB5

    // What to set in ctrl registers
    // TCCR1A - COM, WGM
    // TCCR1B - WGM, CS
    // TCCR1C - Nothing
 
    // Set prescaler to clk_io/256 - CS1 2:0 = 4
    TCCR1B |= _BV(CS12) | _BV(WGM12) | _BV(WGM13);
    TCCR1B &= ~_BV(CS11) & ~_BV(CS10);

    // Set TIMER1 to fast pwm mode, set to non-inverting mode
    TCCR1A |= _BV(COM1A1) | _BV(WGM11);
    TCCR1A &= ~_BV(COM1A0) & ~_BV(WGM10);

    // Set ICR1 (which defines TOP) to 1250
    ICR1 = 125;

    OCR1A = 40;

    DDRB |= _BV(PWM_PIN);
    // TCCR0B |= (1 << COM0A1);
    // TCCR0B &= ~(1 << COM0A0); 

    // TODO:
    // Set the timer to the greatest

}
