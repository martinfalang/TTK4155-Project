/**
 * @file delay.h
 * @author Kristian Brudeli
 *         Martin Falang
 *         Eirik Flemsæter Falck
 * @brief Implements a functions for variable delay in milliseconds. This is 
 *        needed by the @ref buzzer.h module because AVR's built in @c _delay_ms
 *        function only support delay durations known at compile time. 
 * @version 0.1
 * @date 2019-11-18
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef DELAY_H
#define DELAY_H

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>


////////////////////////////////////////////////////////////////////////////////
// Public functions
////////////////////////////////////////////////////////////////////////////////

void var_delay_ms(uint16_t ms);


#endif // DELAY_H