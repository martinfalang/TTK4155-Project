
#include <stdio.h>
#include <avr/io.h>
#include "../../lib/inc/uart.h"

#include "../../lib/inc/defines.h"
#include <util/delay.h>

#include "../../lib/inc/spi.h"
#include "../../lib/inc/can.h"
#include "../../lib/inc/mcp2515_defines.h"

#include "ir.h"

#include "motor.h"


int main(void) {
    uart_init();
    motor_init();
    can_init(MODE_NORMAL);
    printf("All inits ran successfully!\n");

    while (1) {
        const can_msg_t *joy_recv_msg;

        if (can_new_msg()) {
            joy_recv_msg = can_get_recv_msg();
            can_print_msg(joy_recv_msg);

            motor_set_speed(joy_recv_msg->data[1]);
        }
        _delay_ms(10);
        
    }
}
