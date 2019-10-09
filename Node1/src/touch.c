
#include "touch.h"

#include <avr/io.h> // For IO operations
#include <stdio.h> // For printf()

void touch_init() {
    DDRB &= ~(1 << TOUCH_RIGHT_BTN);
    DDRB &= ~(1 << TOUCH_LEFT_BTN);
}

touch_btn_t touch_read_btns() {

    touch_btn_t btns = {.right = 0, .left = 0};

    if (PINB & (1 << TOUCH_RIGHT_BTN)) {
        btns.right = 1;
    }

    if (PINB & (1 << TOUCH_LEFT_BTN)) {
        btns.left = 1;
    }
    
    return btns;
}

void touch_test() {
    touch_btn_t btns = touch_read_btns();
    touch_slider_t slider = touch_read_sliders();
    printf("Left button: %i     Right button: %i    ", btns.left, btns.right);
    printf("Left slider: %i     Right slider: %i\n", slider.left, slider.right);
}

touch_slider_t touch_read_sliders() {
    touch_slider_t sliders = {.left = -1, .right = -1};

    sliders.left = adc_read(TOUCH_SLIDER_LEFT);
    sliders.left = sliders.left * 100 / ADC_MAX_VALUE;

    sliders.right = adc_read(TOUCH_SLIDER_RIGHT);
    sliders.right = sliders.right * 100 / ADC_MAX_VALUE;

    return sliders;
}