
#include <stdio.h>
#include <avr/io.h>
#include "../../lib/inc/uart.h"

#include "../../lib/inc/defines.h"
#include <util/delay.h>
#include "../../lib/inc/mcp2515_defines.h"
#include "../../lib/inc/can.h"
#include "../../lib/inc/message_defs.h"


#include "../inc/pid.h"

#include "ir.h"

#include "motor.h"
#include "enocder.h"
#include "solenoid.h"



int main(void) {
    uart_init();
    motor_init();
    encoder_init();    
    solenoid_init();
    can_init(MODE_NORMAL);
    printf("All inits ran successfully!\n");

    _delay_ms(100);
    // solenoid_give_pulse();

    const can_msg_t *recv_msg;

    while (1) {
        // ir_test();

        if (can_new_msg()) {
            recv_msg = can_get_recv_msg();

            switch (recv_msg->sid)
            {
            case CTRL_SID:
                // User control input

                // printf("\n\nRecv:\n");
                // printf("Joystick dir: %i\n", recv_msg->data[JOY_DIR_IDX]);
                printf("JD %i\n", recv_msg->data[JOY_DIR_IDX]);
                // printf("Joystick X pos: %i\tJoystick Y pos: %i\n", recv_msg->data[1], recv_msg->data[2]);
                // printf("Touch btns:\tLeft: %i\tRight: %i\n", recv_msg->data[3], recv_msg->data[4]);
                // printf("Touch sliders:\tLeft: %i\tRight: %i\n", recv_msg->data[5], recv_msg->data[6])
                break;
            case START_GAME_SID:
                printf("Start!\n");
                break;
            case STOP_GAME_SID:
                printf("Stop!\n");
                break;
            case CALIBRATE_SID:
                printf("Calibrate!\n");
                break;
            default:
                break;
            }
        }      
    }
}
