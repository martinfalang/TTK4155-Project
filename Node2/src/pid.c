#include "pid.h"
#include <avr/interrupt.h>
#include "../../lib/inc/defines.h"

#include <stdio.h>

void pid_init(pid_t *pid, uint16_t kp, uint16_t ki, uint16_t kd, uint8_t timestep) {
    pid->Kp = kp;
    pid->Ki = ki;
    pid->Kd = kd;
    pid->T  = timestep;

    pid->current_error = 0;
    pid->previous_error = 0;
    pid->cumulative_error = 0;

    pid->output = 0;


    // Setup timer
    // CTC mode with TOP = OCR5A, disconnected pin
    TCCR5B |= (1 << WGM02) | (1 << CS51) | (1 << CS50);
    TCCR5A = 0;

    uint32_t ocr = (uint32_t)F_CPU * (uint32_t)timestep / (2UL * 64UL * 1000UL);
    OCR5A = (uint16_t)ocr;

    TIMSK5 |= (1 << OCIE5A);
    sei();
}


uint16_t pid_next_output(pid_t *pid, uint16_t current, uint16_t setpoint) {
    pid->previous_error = pid->current_error;
    pid->current_error = setpoint - current;
    pid->cumulative_error += pid->current_error;

    pid->output = pid->Kp * pid->current_error
                + pid->T * pid->Ki * pid->cumulative_error
                + pid->Kd / pid->T * (pid->current_error - pid->previous_error);

    return pid->output;
}


ISR(TIMER5_COMPA_vect) {

}
