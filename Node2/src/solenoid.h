/**
 * @file solenoid.h
 * @author Kristian Brudeli
 *         Martin Falang
 *         Eirik Flemsæter Falck
 * @brief Implements functions for driving the solenoid on the gameboard. 
 * @version 0.1
 * @date 2019-11-18
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef SOLENOID_H
#define SOLENOID_H

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////

#include <avr/io.h> // TODO: Why is that here

////////////////////////////////////////////////////////////////////////////////
// Defines
////////////////////////////////////////////////////////////////////////////////

#define SOLENOID_PIN PE5  // Pin 3 on the arduino s


/**
 * @brief Initializes the solenoid control pin
 * 
 */
void solenoid_init(void);

/**
 * @brief Gives a short pulse to the solenoid
 * 
 */
void solenoid_give_pulse(void);


#endif  // SOLENOID_H