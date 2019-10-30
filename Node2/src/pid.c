#include "../inc/pid.h"
#include <avr/interrupt.h>



void pid_init(pid_t *pid, int kp, int ki, int kd) {
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
    TCCR5B |= (1 << WGM02);
    TCCR5A = 0;
    
}


void pid_next(pid_t *pid, uint16_t current, uint16_t setpoint) {

}



