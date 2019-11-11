
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
float kp = 0.8;
float ki = 0.01;
float kd = 0.08;
float t  = 0.01;  // sample time of pid

int16_t pos;

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

            int16_t r = recvmsg->data[1] - 51;
            motor_pid.setpoint = r;
            printf("Pos: %i\n", pos);
            // printf("r: %d   u: %d\n", (int)(10 * motor_pid.setpoint), (int)(10 * motor_pid.output));
        }
    }

    return 0;
}   


ISR(TIMER5_COMPA_vect) {
    // int16_t enc = encoder_read();
    // pos += enc;
    pid_next_output(&motor_pid);
    motor_pid.measurement = encoder_read();
    motor_set_speed(motor_pid.output);
}

