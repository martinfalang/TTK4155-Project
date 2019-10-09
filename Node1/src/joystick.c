
#include "joystick.h"
#include <stdio.h>

void joystick_init() {
    // Set PB3 to input
    DDRB &= ~(1 << JOY_BTN);

    // Enable internal pull-up on PB3
    PORTB |= (1 << JOY_BTN);
}

void joystick_test() {
    pos_t pos = joystick_get_position();
    printf("X: %i   Y: %i   Dir: %i   Joystick btn: %i\n", pos.x, pos.y, joystick_get_direction(), joystick_read_btn());
}

pos_t joystick_read_x_and_y_raw() {
    pos_t pos;

    pos.x = adc_read(JOY_X_CH);
    pos.y = adc_read(JOY_Y_CH);

    return pos;
}

pos_t joystick_get_position() {
    pos_t pos;

    pos = joystick_read_x_and_y_raw();

    // Scaled to percent
    pos.x = pos.x * 100/ADC_MAX_VALUE;
    pos.y = pos.y * 100/ADC_MAX_VALUE;

    return pos;
}

int joystick_read_btn() {
    
    if (!(PINB & (1 << JOY_BTN))) {
        return 1;
    }
    else {
        return 0;
    }
}

joy_btn_dir_t joystick_get_direction() {
    pos_t pos = joystick_get_position();

    if (pos.x  >= THRESHOLD_RIGHT) {
        return RIGHT;
    }
    else if (pos.x <= THRESHOLD_LEFT) {
        return LEFT;
    }
    else if (pos.y >= THRESHOLD_UP) {
        return UP;
    }
    else if (pos.y <= THRESHOLD_DOWN) {
        return DOWN;
    }
    else {
        return NEUTRAL;
    }
}
