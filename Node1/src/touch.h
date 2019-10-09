#ifndef TOUCH_H
#define TOUCH_H

#include <avr/io.h>
#include "adc.h"


#define TOUCH_RIGHT_BTN PB1
#define TOUCH_LEFT_BTN  PB2
#define TOUCH_SLIDER_RIGHT ADC_CH4
#define TOUCH_SLIDER_LEFT  ADC_CH3 

typedef struct touch_btn {
    int right;
    int left;
} touch_btn_t;

typedef struct touch_slider {
    int left;
    int right;
} touch_slider_t;

void touch_init();

void touch_test();

touch_btn_t touch_read_btns();

touch_slider_t touch_read_sliders();

#endif // TOUCH_H