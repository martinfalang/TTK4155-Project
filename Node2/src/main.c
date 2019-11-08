
#include <stdio.h>
#include <avr/io.h>
#include "../../lib/inc/uart.h"

#include "../../lib/inc/defines.h"
#include <util/delay.h>

#include <avr/interrupt.h>

#include "ir.h"
#include "pid.h"
#include "dac.h"
#include "motor.h"
#include "enocder.h"
#include "solenoid.h"
#include "../../lib/inc/mcp2515_defines.h"
#include "../../lib/inc/can.h"


pid_t motor_pid;
float kp = 0.2;
float ki = 0.01;
float kd = 0;
float t  = 0.05;  // sample time of pid


int main(void) {
    uart_init();
    ir_init();
    dac_init();
    motor_init();
    encoder_init();
    solenoid_init();
    can_init(MODE_NORMAL);
    pid_init(&motor_pid, kp, ki, kd, t);
    motor_pid.setpoint = 0;

    printf("All inits ran successfully!\n");

    const can_msg_t *recvmsg;

    while (1) {
        if (can_new_msg()) {
            recvmsg = can_get_recv_msg();

            int16_t r = recvmsg->data[1] - 50;
            motor_pid.setpoint = r;
        }
    }

    return 0;
}   


ISR(TIMER5_COMPA_vect) {
    pid_next_output(&motor_pid);
    motor_pid.measurement = encoder_read();
    printf("r: %d   u: %d\n", (int)(10 * motor_pid.setpoint), (int)(10 * motor_pid.output));
    motor_set_speed(motor_pid.output);
}

