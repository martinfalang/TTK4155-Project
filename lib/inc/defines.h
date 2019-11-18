/**
 * @file defines.h
 * @author Kristian Brudeli
 *         Martin Falang
 *         Eirik Flemsæter Falck
 * @brief Defines macros useful in both nodes. 
 * @version 0.1
 * @date 2019-11-18
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef DEFINES_H
#define DEFINES_H

////////////////////////////////////////////////////////////////////////////////
// Defines
////////////////////////////////////////////////////////////////////////////////

// Debug - set this to 1 to allow test functions
#define DEBUG                   0
#define COMPILE_SRAM_TEST       0
#define COMPILE_TOUCH_TEST      0
#define COMPILE_JOYSTICK_TEST   0
#define COMPILE_CAN_TEST        0

// Global CPU frequency
#if defined (__AVR_ATmega162__)
    #define F_CPU 4915200
#elif defined (__AVR_ATmega2560__)
    #define F_CPU 16000000
#else
    #define F_CPU 0
#endif

#endif /* DEFINES_H */