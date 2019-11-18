/**
 * @file touch.h
 * @author Kristian Brudeli
 *         Martin Falang
 *         Eirik Flemsæter Falck
 * @brief Implements functions to check the state of the touch buttons and 
 *        sliders. 
 * @version 0.1
 * @date 2019-11-18
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef TOUCH_H
#define TOUCH_H

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////

#include <avr/io.h>

#include "adc.h"

////////////////////////////////////////////////////////////////////////////////
// Defines
////////////////////////////////////////////////////////////////////////////////

#define TOUCH_RIGHT_BTN         PB1
#define TOUCH_LEFT_BTN          PB2
#define TOUCH_SLIDER_RIGHT      ADC_CH4
#define TOUCH_SLIDER_LEFT       ADC_CH3 

////////////////////////////////////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief A struct holding the left and right button states.
 *        0: unpressed
 *        1: pressed
 * 
 */
typedef struct touch_btn {
    int right;
    int left;
} touch_btn_t;

/**
 * @brief A struct holding the left and right slider position.
 * 
 */
typedef struct touch_slider {
    int left;
    int right;
} touch_slider_t;

////////////////////////////////////////////////////////////////////////////////
// Function declarations
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Initialize the touch buttons and sliders
 * 
 */
void touch_init();

/**
 * @brief Read the current buttons state
 * 
 * @return touch_btn_t A struct holding the current button state, see 
 *         @c touch_btn_t
 */
touch_btn_t touch_read_btns();

/**
 * @brief Read the current slider position
 * 
 * @return touch_slider_t A struct holding the current slider position, see
 *         @c touch_slider_t 
 */
touch_slider_t touch_read_sliders();

#if COMPILE_TOUCH_TEST
void touch_test();
#endif // COMPILE_TOUCH_TEST

#endif // TOUCH_H