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
#include "timer.h"

void heartbeat_init() {
    DDRE |= 1 << DDE0;
}

void heartbeat()
{
    PORTE ^= 1 << PE0;
}

int main(void)
{
    // Init modules
    heartbeat_init();
    uart_init(); // So we can communicate with the terminal connected via JTAG
    xmem_init();
    adc_init();
    joystick_init();
    touch_init();
    timer_init();

    can_init(MODE_NORMAL);
    
    oled_init();
    oled_menu_init();

    printf("All inits ran successfully!\n");

    joy_btn_dir_t joystick_dir;
    pos_t joystick_pos;
    touch_btn_t touch_btns;
    touch_slider_t touch_sliders;

    can_msg_t msg;

    while(1) {
        
        if (timer_get_heartbeat_timeout()) {
            heartbeat();
        }

        if (timer_get_can_timeout()) {

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
        }

        if (timer_get_oled_timeout()) {
            oled_menu_update();
        }
    } 
}
