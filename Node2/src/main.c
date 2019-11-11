
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
#include "pwm.h"

pid_t motor_pid;
float kp = 1;
float ki = 0;
float kd = 0.02;
float t  = 0.01;  // sample time of pid


int main(void) {
    uart_init();
    ir_init();
    dac_init();
    motor_init();
    encoder_init();
    solenoid_init();
    can_init(MODE_NORMAL);
    pwm_init();

    pid_init(&motor_pid, kp, ki, kd, t);
    motor_pid.setpoint = 0;

    printf("All inits ran successfully!\n");
    printf("#r,u,v\n");

    const can_msg_t *recvmsg;

    int solenoid_cmd_prev = 0;

    while (1) {
        if (can_new_msg()) {
            recvmsg = can_get_recv_msg();

            for (int i = 0; i < recvmsg->length; ++i) {
                printf("%.2X ", recvmsg->data[i]);
            }
            putchar('\n');

            int16_t r = recvmsg->data[1] - 51;
            motor_pid.setpoint = r;

            // fire solenoid once when joystick is pointed up
            if (recvmsg->data[0] == 2 && solenoid_cmd_prev != recvmsg->data[0]) {
                solenoid_cmd_prev = recvmsg->data[0];
                solenoid_give_pulse();
            }
            else if (recvmsg->data[0] != 2) {
                solenoid_cmd_prev = recvmsg->data[0];
            }

            // Turn the servo using the touch sliders
            int16_t degrees = 180 - (int16_t)(recvmsg->data[6] * 1.8);
            printf("deg: %i\n", degrees);

            pwm_set_duty_cycle(degrees);
            // printf("Pos: %i\n", pos);
            // printf("r: %d   u: %d\n", (int)(10 * motor_pid.setpoint), (int)(10 * motor_pid.output));
            // putchar('!');
            // printf("%d", motor_pid.setpoint);
            // putchar(',');
            // printf("%d", motor_pid.output);
            // putchar(',');
            // printf("%d", motor_pid.measurement);
            // putchar('\n');
        }
    }

    return 0;
}   


ISR(TIMER5_COMPA_vect) {
    pid_next_output(&motor_pid);
    motor_pid.measurement = encoder_read();
    motor_set_speed(motor_pid.output);
}

