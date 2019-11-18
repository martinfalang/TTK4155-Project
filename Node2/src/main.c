
////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////

// Lib includes
#include "../../lib/inc/uart.h"
#include "../../lib/inc/defines.h"
#include "../../lib/inc/mcp2515_defines.h"
#include "../../lib/inc/can.h"
#include "../../lib/inc/message_defs.h"
#include "../../lib/inc/message_defs.h"
#include "../../lib/inc/timer.h"

// Node2 includes
#include "ir.h"
#include "pid.h"
#include "dac.h"
#include "motor.h"
#include "enocder.h"
#include "solenoid.h"
#include "pwm.h"
#include "game_logic.h"

// AVR and C includes
#include <stdio.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

////////////////////////////////////////////////////////////////////////////////
// Private functions
////////////////////////////////////////////////////////////////////////////////

pid_t motor_pos_pid;
const float T  = 0.01;  // sample time of pid

extern can_msg_t endofgame_msg;  // TODO: Bad?

////////////////////////////////////////////////////////////////////////////////
// Main function
////////////////////////////////////////////////////////////////////////////////

int main(void) {
    uart_init(); putchar('\n');
    ir_init();
    pwm_init();
    dac_init();
    motor_init();
    encoder_init();
    solenoid_init();
    can_init(MODE_NORMAL);

    timer_init();

    // pid_init(&motor_vel_pid, kp, ki, kd, T, output_maximum);
    // motor_vel_pid.setpoint = 0;
    motor_pos_pid.output_maximum = -1;
    motor_pos_pid.output_minimum = 40;
    motor_pos_pid.T = T;
    motor_pos_pid.error_deadzone = 20;

    printf("All inits ran successfully!\n");

    const can_msg_t *recvmsg;

    // TODO: Make this less tight
    while (1) {
        if (can_new_msg()) {
            recvmsg = can_get_recv_msg();
            
            // TODO: Change cases with defines from file
            switch (recvmsg->sid)
            {
            case CALIBRATE_SID: // calibrate
                encoder_calibrate();
                break;
            case START_GAME_SID: // start game
                game_init(recvmsg->data[0], &motor_pos_pid);
            case CTRL_SID: // playing game
                game_play(recvmsg, &motor_pos_pid);
                break;
            case STOP_GAME_SID:
                endofgame_msg.data[0] = 0;
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

////////////////////////////////////////////////////////////////////////////////
// Interrupt service routine
////////////////////////////////////////////////////////////////////////////////

ISR(TIMER5_COMPA_vect) {
    motor_pos_pid.measurement_raw += encoder_read_raw();
    motor_pos_pid.measurement = encoder_scale_measurement(motor_pos_pid.measurement_raw, 0, 1000);
    pid_next_output(&motor_pos_pid);
    motor_set_speed(motor_pos_pid.output);
}

