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
#include "oled.h"
#include "oled-menu.h"

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
    
    oled_init();
    oled_menu_init(OLED_BUFFER_BASE);

    printf("All inits ran successfully!\n");

    joy_btn_dir_t joystick_dir;
    pos_t joystick_pos;
    touch_btn_t touch_btns;
    touch_slider_t touch_sliders;

    can_msg_t msg;

    while(1) {
        // _delay_ms(200);
        heartbeat();
        joystick_dir = joystick_get_direction();
        joystick_pos = joystick_get_position();
        
        touch_btns = touch_read_btns();
        touch_sliders = touch_read_sliders();

        msg.sid = 0;
        msg.length = 7;
        msg.data[0] = joystick_dir;
        msg.data[1] = joystick_pos.x;
        msg.data[2] = joystick_pos.y;
        msg.data[3] = touch_btns.left;
        msg.data[4] = touch_btns.right;
        msg.data[5] = touch_sliders.left;
        msg.data[6] = touch_sliders.right;

        can_send(&msg);

        printf("\n\nSent message:\n");
        can_print_msg(&msg);

        // const can_msg_t *recv_msg;


        // if (can_new_msg()) {
        //     recv_msg = can_get_recv_msg();
        //     printf("\n\nReceived:\n");
        //     can_print_msg(recv_msg);
        // }
        // printf("\n\nSent:\n");
        // joystick_test();
        // if (oled_menu_should_update())
        // {
        //     printf("Oled menu should update\n");
        //     oled_menu_update(OLED_BUFFER_BASE);
        // }
        oled_menu_update(OLED_BUFFER_BASE);
        _delay_ms(50);

        // oled_menu_update_if_needed();
        

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
        // joystick_test();
        // touch_test();
        // printf("\n");
#endif // DEBUG
    } 
}
