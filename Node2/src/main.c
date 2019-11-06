
#include <stdio.h>
#include <avr/io.h>
#include "../../lib/inc/uart.h"

#include "../../lib/inc/defines.h"
#include <util/delay.h>

#include "../../lib/inc/spi.h"
#include "../../lib/inc/can.h"
#include "../../lib/inc/mcp2515_defines.h"

#include "ir.h"

#include <avr/interrupt.h>

int main(void) {
    uart_init();

    can_init(MODE_NORMAL);
    printf("All inits ran successfully!\n");
    // ir_init();

    while (1) {
        // ir_test();
        const can_msg_t *recv_msg;

        if (can_new_msg()) {
            recv_msg = can_get_recv_msg();
            printf("\n\nRecv:\n");
            printf("Joystick dir: %i\n", recv_msg->data[0]);
            printf("Joystick X pos: %i\tJoystick Y pos: %i\n", recv_msg->data[1], recv_msg->data[2]);
            printf("Touch btns:\tLeft: %i\tRight: %i\n", recv_msg->data[3], recv_msg->data[4]);
            printf("Touch sliders:\tLeft: %i\tRight: %i\n", recv_msg->data[5], recv_msg->data[6]);
        }

        // _delay_ms(100);
        
    }
}
