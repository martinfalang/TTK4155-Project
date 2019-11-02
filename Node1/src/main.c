/*
 * TestProject.c
 *
 * Created: 28.08.2019 12.19.50
 * Author : eirik
 */

#include "../../lib/inc/defines.h"

#include <stdio.h>

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>

#include "../../lib/inc/uart.h"
#include "xmem.h"
#include "adc.h"
#include "joystick.h"
#include "touch.h"
#include "../../lib/inc/mcp2515_defines.h"
#include "../../lib/inc/can.h"

void heartbeat_init() {
    DDRE |= 1 << DDE0;
}

void heartbeat()
{
    PORTE ^= 1 << PE0;
}

int main(void)
{
    heartbeat_init();
    uart_init(); // So we can communicate with the terminal connected via JTAG
    xmem_init();
    adc_init();
    joystick_init();
    touch_init();

    can_init(MODE_NORMAL);
    

    printf("All inits ran successfully!\n");

    joy_btn_dir_t joystick_dir;
    pos_t joystick_pos;

    while(1) {
        _delay_ms(200); // _delay_ms(10);
        heartbeat();
        joystick_dir = joystick_get_direction();
        joystick_pos = joystick_get_position();

        // can_msg_t joy_packet = {
        //     .sid = 0,
        //     .length = 3,
        //     .data[0] = joystick_dir,
        //     .data[1] = joystick_pos.x,
        //     .data[2] = joystick_pos.y,
        // };
        // can_send(&joy_packet);
#if DEBUG
        // // can_loopback_test();
        // const can_msg_t *recv;
        // if (can_new_msg()) {
        //     recv = can_get_recv_msg();
        //     printf("\n\nRecv:\n");
        //     can_print_msg(recv);
        //     printf("\n");
        // }
        // can_test_node_transmission();
        joystick_test();
        // touch_test();
        // printf("\n");
#endif // DEBUG
    } 
}
