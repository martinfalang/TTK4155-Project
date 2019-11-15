#ifndef JOYSTICK_H
#define JOYSTICK_H

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////

#include "adc.h"
#include <avr/io.h>
#include <stdint.h>

////////////////////////////////////////////////////////////////////////////////
// Defines
////////////////////////////////////////////////////////////////////////////////

#define JOY_X_CH ADC_CH1
#define JOY_Y_CH ADC_CH2
#define JOY_BTN PB3

#define THRESHOLD_UP 90
#define THRESHOLD_DOWN 10
#define THRESHOLD_LEFT 10
#define THRESHOLD_RIGHT 90

////////////////////////////////////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief A struct representing the position of the joystick
 * 
 */
typedef struct pos {
    uint8_t x;
    uint8_t y;
} pos_t;

////////////////////////////////////////////////////////////////////////////////
// Enums
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Possible joystick direction
 * 
 */
typedef enum joy_btn_dir {
    LEFT,
    RIGHT,
    UP,
    DOWN,
    NEUTRAL
} joy_btn_dir_t;

////////////////////////////////////////////////////////////////////////////////
// Function declarations
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Initialize joystick pins
 * 
 */
void joystick_init();

/**
 * @brief Read the raw ADC value of the joystick axis
 * 
 * @return pos_t A position struct with x- and y-values
 */
pos_t joystick_read_x_and_y_raw();

/**
 * @brief Reads the joystick position, scaling it from 0 (left/down) to 100 
 *        (up/right)
 * 
 * @return pos_t A position struct with x- and y-values scaled from 0 to 100.
 */
pos_t joystick_get_position();

/**
 * @brief Interprets the joystick position to give a direction
 * 
 * @return joy_btn_dir_t Direction of the joystick
 */
joy_btn_dir_t joystick_get_direction();

/**
 * @brief Reads the joystick button
 * 
 * @return uint8_t 
 */
uint8_t joystick_read_btn();


#if COMPILE_JOYSTICK_TEST
void joystick_test();
#endif // COMPILE_JOYSTICK_TEST

#endif // JOYSTICK_h