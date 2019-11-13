
#include <stdio.h>
#include <stdbool.h>
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
#include "game_logic.h"


pid_t motor_pos_pid;
float T  = 0.01;  // sample time of pid

int main(void) {
    uart_init();
    putchar('\n');
    ir_init();

    encoder_init();
    // encoder_calibrate();  // run this when calibrate message is received

    solenoid_init();
    can_init(MODE_NORMAL);
    pwm_init();
    dac_init();
    motor_init();

    // pid_init(&motor_vel_pid, kp, ki, kd, T, output_maximum);
    // motor_vel_pid.setpoint = 0;
    motor_pos_pid.output_maximum = -1;
    motor_pos_pid.output_minimum = 40;
    motor_pos_pid.T = T;

    printf("All inits ran successfully!\n");

    const can_msg_t *recvmsg;

    // TODO: Make this less tight
    while (1) {
        if (can_new_msg()) {
            recvmsg = can_get_recv_msg();
            
            // TODO: Change cases with defines from file
            switch (recvmsg->sid)
            {
            case 456: // calibrate
                encoder_calibrate();
                break;
            case 234: // start game
                game_init(recvmsg->data[0], &motor_pos_pid);
            case 345: // playing game
                game_play(recvmsg, &motor_pos_pid);
                break;
            case 123:
                game_over();
                break;
            default:
                printf("Got unknown CAN message. Got: %i\n", recvmsg->sid);
                break;
            }
         
        }   
    }
    

    return 0;
}   

ISR(TIMER5_COMPA_vect) {
    motor_pos_pid.measurement_raw += encoder_read_raw();
    motor_pos_pid.measurement = encoder_scale_measurement(motor_pos_pid.measurement_raw, 0, 1000);
    motor_set_speed(motor_pos_pid.output);
    printf("INT\n");
}

