/*
 * Byggern 2019
 *
 * Created: 28.08.2019 12.19.50
 * Authors :    Kristian Brudeli
 *              Martin Falang
 *              Eirik Flemsæter Falck
 */

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////

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
#include "../../lib/inc/message_defs.h"
#include "../../lib/inc/can.h"
#include "../../lib/inc/timer.h"
#include "oled.h"
#include "oled-menu.h"
#include "game.h"
#include "buzzer.h"
#include "songs/star_wars.h"

////////////////////////////////////////////////////////////////////////////////
// Private functions
////////////////////////////////////////////////////////////////////////////////

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
        .sid = CTRL_SID,
        .length = 7,
        .data[JOY_DIR_IDX] = joystick_dir,
        .data[JOY_POS_X_IDX] = joystick_pos.x,
        .data[JOY_POS_X_IDX] = joystick_pos.y,
        .data[BTNS_LEFT_IDX] = touch_btns.left,
        .data[BTNS_RIGHT_IDX] = touch_btns.right,
        .data[SLIDER_LEFT_IDX] = touch_sliders.left,
        .data[SLIDER_RIGHT_IDX] = touch_sliders.right,
    };

    can_send(&msg);

#if DEBUG   
    printf("\n\nSent message:\n");
    can_print_msg(&msg);
#endif // DEBUG
}

////////////////////////////////////////////////////////////////////////////////
// Main function
////////////////////////////////////////////////////////////////////////////////

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
    // buzzer_init();

    can_init(MODE_NORMAL);
    
    oled_init();
    oled_menu_init();

    const can_msg_t *recv_msg;

    printf("All inits ran successfully!\n");    

    // buzzer_play_song_P(star_wars_melody, star_wars_note_types, STAR_WARS_LENGTH);

    while(1) {
        
        if (timer_get_1Hz_timeout()) {
            heartbeat();
        }

        if (can_new_msg()) {
             
            recv_msg = can_get_recv_msg();

            switch (recv_msg->sid)
            {
            case STOP_GAME_SID:
                printf("Beam broken!\n");
                game_stop();
                break;

            case SCORE_SID:
                game_set_score(recv_msg->data[0]);
            default:
                break;
            }
        }

        if (timer_get_6Hz_timeout() && game_is_playing()) {
            printf("Controller data sent\n");
            _send_joystick_and_touch_data();
        }

        if (timer_get_60Hz_timeout()) {
            oled_menu_update();
        }
    } 
}
