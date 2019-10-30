
#include <stdio.h>
#include <avr/io.h>
#include "../../lib/inc/uart.h"

#include "../../lib/inc/defines.h"
#include <util/delay.h>

#include "../../lib/inc/spi.h"
#include "../../lib/inc/can.h"
#include "../../lib/inc/mcp2515_defines.h"

#include "ir.h"


int main(void) {
    uart_init();

    can_init(MODE_NORMAL);
    printf("All inits ran successfully!\n");
    // ir_init();

    while (1) {
        // ir_test();
        const can_msg_t *joy_recv_msg;

        if (can_new_msg()) {
            joy_recv_msg = can_get_recv_msg();
            printf("\n\nRecv:\n");
            printf("Joystick dir: %i\n", joy_recv_msg->data[1]);
            printf("Joystick X pos: %i\tJoystick Y pos: %i\n", joy_recv_msg->data[1], joy_recv_msg->data[2]);
        }
        _delay_ms(10);
        
    }
}
