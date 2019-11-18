/**
 * @file motor.h
 * @author Kristian Brudeli
 *         Martin Falang
 *         Eirik Flemsæter Falck
 * @brief Implements functions for driving the motor attached to the gamebox. 
 * @version 0.1
 * @date 2019-11-18
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef MOTOR_H
#define MOTOR_H


////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////

#include <avr/io.h>


////////////////////////////////////////////////////////////////////////////////
// Defines
////////////////////////////////////////////////////////////////////////////////

// MJ1
#define DIR PH1
#define EN  PH4

#define MOTOR_MAX_INPUT 80


////////////////////////////////////////////////////////////////////////////////
// Function declarations
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Initializes the motor 
 * 
 */
void motor_init(void);

/**
 * @brief Enables or disables the motor
 * 
 * @param en @p en @c = @c 1 enables the motor, @p en @c = @c 0 disables
 */
void motor_enable(int en);

/**
 * @brief Sets the direction of the motor
 * 
 * @param dir @p dir @c = @c 1 sets the direction one way, @p dir @c = @c 0 sets
 *            the direcion the other way. Which direcition is which way depends
 *            on the motor voltage polarity and have to be figured out 
 *            experimentally. 
 */
void motor_set_dir(int dir);

/**
 * @brief Sets speed of motor. A speed of @c +255 is full speed in one 
 *        direction, @c -255 is full speed the other direction. 
 * 
 * @param speed Speed from @c -255 to @c 255
 */
void motor_set_speed(int speed);



#endif  // MOTOR_H
