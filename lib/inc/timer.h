/**
 * @file timer.h
 * @author Kristian Brudeli
 *         Martin Falang
 *         Eirik Flemsæter Falck
 * @brief Implements timers of different frequency and functions to check if 
 *        they have timed out. 
 * @version 0.1
 * @date 2019-11-18
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef TIMER_H
#define TIMER_H

////////////////////////////////////////////////////////////////////////////////
// Inclues
////////////////////////////////////////////////////////////////////////////////

#include <stdbool.h>

////////////////////////////////////////////////////////////////////////////////
// Defines
////////////////////////////////////////////////////////////////////////////////

#define _1HZ_COUNT          60
#define _6HZ_COUNT          10
#define _10HZ_COUNT         6

#if defined (__AVR_ATmega162__)
#define TIMER_ISR_VECT      TIMER2_COMP_vect

#elif defined (__AVR_ATmega2560__)

#define TIMER_ISR_VECT      TIMER3_COMPA_vect

#endif

////////////////////////////////////////////////////////////////////////////////
// Function declarations
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Initializes timer
 * 
 */
void timer_init(void);

/**
 * @brief Checks if the 60Hz timer has timed out
 * 
 * @return true Has timed out
 * @return false Has not timed out
 */
bool timer_get_60Hz_timeout(void);

/**
 * @brief Checks if the 1Hz counter has timed out 
 * 
 * @return true Has timed out
 * @return false Has not timed out
 */
bool timer_get_1Hz_timeout(void);

/**
 * @brief Checks if the 6Hz counter has timed out 
 * 
 * @return true Has timed out
 * @return false Has not timed out
 */
bool timer_get_6Hz_timeout(void);

/**
 * @brief Checks if the 10Hz counter has timed out 
 * 
 * @return true Has timed out
 * @return false Has not timed out
 */
bool timer_get_10Hz_timeout(void);

#endif // TIMER_H