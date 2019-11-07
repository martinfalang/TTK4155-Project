/*
 * Byggern 2019
 *
 * Created: 28.08.2019 12.19.50
 * Authors :    Kristian Brudeli
 *              Martin Falang
 *              Eirik Flemsæter Falck
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

void _send_joystick_and_touch_data(void) {
    joy_btn_dir_t joystick_dir = joystick_get_direction();
    pos_t joystick_pos = joystick_get_position();
    
    touch_btn_t touch_btns = touch_read_btns();
    touch_slider_t touch_sliders = touch_read_sliders();

    can_msg_t msg = {
        .sid = 0,
        .length = 7,
        .data[0] = joystick_dir,
        .data[1] = joystick_pos.x,
        .data[2] = joystick_pos.y,
        .data[3] = touch_btns.left,
        .data[4] = touch_btns.right,
        .data[5] = touch_sliders.left,
        .data[6] = touch_sliders.right,

    };

    can_send(&msg);

#if DEBUG   
    printf("\n\nSent message:\n");
    can_print_msg(&msg);
#endif // DEBUG
}

int main(void)
{
    // Init modules
    heartbeat_init();
    uart_init();
    xmem_init();
    adc_init();
    joystick_init();
    touch_init();
    timer_init();

    can_init(MODE_NORMAL);
    
    oled_init();
    oled_menu_init();

#if DEBUG
    printf("All inits ran successfully!\n");    
#endif // DEBUG

    while(1) {
        
        if (timer_get_heartbeat_timeout()) {
            heartbeat();
        }

        if (timer_get_can_timeout()) {
            _send_joystick_and_touch_data();
        }

        if (timer_get_oled_timeout()) {
            oled_menu_update();
        }
    } 
}
