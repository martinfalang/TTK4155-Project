// Module for controlling the servo through PWM

// Period 20ms
// Duty cycle * Period in interval [0.9, 2.1] ms

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////

#include <avr/io.h>
#include <avr/interrupt.h>

#include "pwm.h"

////////////////////////////////////////////////////////////////////////////////
// Defines
////////////////////////////////////////////////////////////////////////////////

// See docs/schematics/arduino-mega2560_r3-sch.pdf for schematics
#define PWM_PIN PB5 // OC1A

#define PWM_OFFSET 0 // -7                 // To correct for discrepancies
#define PWM_LOWER_OCR_LIM 55 + PWM_OFFSET  // Lower limit: 55, gives 0.9 ms
#define PWM_UPPER_OCR_LIM 128 + 10 + PWM_OFFSET // Upper limit: 128 gives 2.1 ms

// Degrees comple
#define RIGHT_SERVO_DEGS_LIM 0 // TODO - update based on actual values
#define LEFT_SERVO_DEGS_LIM 180

// General idea: Set one OCR such that we can reset the timer from the interrupt, set the
// other to generate the PWM signal.

// void pwm_init_interrupt(void)
// {
//     // Enable interrupts when timer reaches TOP (defined bu ICR1)
//     TIMSK1 |= (1 << TOV1);

//     // Enable interrupts globally
//     SREG |= (1 << SREG_I);
// }

// static uint8_t dx;
// static int16_t degrees = 0;

// ISR(TIMER1_OVF_vect)
// {
//     if (dx == 1 && degrees > LEFT_SERVO_DEGS_LIM)
//     {
//         dx = -1;
//     }
//     else if (degrees < RIGHT_SERVO_DEGS_LIM)
//     {
//         dx = 1;
//     }

//     degrees += dx;

//     pwm_set_duty_cycle(degrees);
// }

////////////////////////////////////////////////////////////////////////////////
// Public functions
////////////////////////////////////////////////////////////////////////////////

// Initialize pwm in fast_pwm-mode
void pwm_init(void)
{
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

void pwm_set_duty_cycle(int16_t degrees)
{
    // Sets the duty cycle of the pwm signal corresponding to degrees.
    // This should be tuned s.t. 0 degrees equals 3-O'clock, as in polar coordinates
    // and 180 degrees to 9-O'clock, the same as pi in polar coordinates
    // and 90 degrees should be straight up

    // Convert degrees to number of counter ticks
    uint8_t ticks = PWM_LOWER_OCR_LIM + degrees * (PWM_UPPER_OCR_LIM - PWM_LOWER_OCR_LIM) / (LEFT_SERVO_DEGS_LIM - RIGHT_SERVO_DEGS_LIM);

    // // Saturate the output if it is outside limits
    // if (ticks > PWM_UPPER_OCR_LIM)
    //     ticks = PWM_UPPER_OCR_LIM;

    // if (ticks < PWM_LOWER_OCR_LIM)
    //     ticks = PWM_LOWER_OCR_LIM;

    // OCR1A = ticks;

    if (PWM_LOWER_OCR_LIM <= ticks && ticks <= PWM_UPPER_OCR_LIM)
        OCR1A = ticks;
       
    // ticks = PWM_UPPER_OCR_LIM;

    // if (ticks < PWM_LOWER_OCR_LIM)
    //     ticks = PWM_LOWER_OCR_LIM;

}
