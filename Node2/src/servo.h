/**
 * @file servo.h
 * @author Kristian Brudeli
 *         Martin Falang
 *         Eirik Flemsæter Falck
 * @brief Implements functions for controller the servo motor. 
 * @version 0.1
 * @date 2019-11-18
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef SERVO_H
#define SERVO_H

/**
 * @brief Initialized the PWM for the servo motor
 * 
 */
void servo_init(void);

/**
 * @brief Sets the correct duty cycle to achieve the desired @p degree .
 * 
 * @param degrees The degree to position the servo motor. Max range: [0, 180]
 */
void servo_set_angle(int16_t degrees);

#endif /* SERVO_H */