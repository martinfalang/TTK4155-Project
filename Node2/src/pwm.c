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
 
    // Set prescaler to clk_io/256 - CS1 2:0 = 4
    TCCR1B |= _BV(CS12) | _BV(WGM12) | _BV(WGM13);
    TCCR1B &= ~_BV(CS11) & ~_BV(CS10);

    // Set TIMER1 to fast pwm mode, set to non-inverting mode
    TCCR1A |= _BV(COM1A1) | _BV(WGM11);
    TCCR1A &= ~_BV(COM1A0) & ~_BV(WGM10);

    // Set ICR1 (which defines TOP) to 1250
    ICR1 = 1250;

    pwm_set_duty_cycle(90);

    // Set PWM pin as output. Use OC1A - PB5
    // This also activates the signal
    DDRB |= _BV(PWM_PIN);
}


#define PWM_LOWER_OCR_LIM 55  // Lower limit: 55, gives 0.9 ms
#define PWM_UPPER_OCR_LIM 128 // Upper limit: 128 gives 2.1 ms

// Degrees comple
#define RIGHT_SERVO_DEGS_LIM 0 // TODO - update based on actual values
#define LEFT_SERVO_DEGS_LIM 180

void pwm_set_duty_cycle(uint8_t degrees) {
    // Sets the duty cycle of the pwm signal corresponding to degrees.
    // This should be tuned s.t. 0 degrees equals 3-O'clock, as in polar coordinates
    // and 180 degrees to 9-O'clock, the same as pi in polar coordinates
    // and 90 degrees should be straight up

    // Convert degrees to number of counter ticks
    uint8_t ticks = PWM_LOWER_OCR_LIM 
                    + degrees * (PWM_UPPER_OCR_LIM - PWM_LOWER_OCR_LIM) 
                    / (LEFT_SERVO_DEGS_LIM - RIGHT_SERVO_DEGS_LIM);

    // Saturate the output if it is outside limits
    if (ticks > PWM_UPPER_OCR_LIM) ticks = PWM_UPPER_OCR_LIM;
    if (ticks < PWM_LOWER_OCR_LIM) ticks = PWM_LOWER_OCR_LIM;

    OCR1A = ticks;
}
