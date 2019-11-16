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
 * @brief Initializes timer2
 * 
 */
void timer_init(void);

/**
 * @brief Checks if the OLED timer have timed out and should update the screen
 * 
 * @return true Has timed out
 * @return false Has not timed out
 */
bool timer_get_60Hz_timeout(void);

/**
 * @brief Checks if the heartbeat timer has timed out and should toggle the LED
 * 
 * @return true Has timed out
 * @return false Has not timed out
 */
bool timer_get_1Hz_timeout(void);

/**
 * @brief Check if the CAN timer has timed out and should send a CAN message
 * 
 * @return true Has timed out
 * @return false Has not timed out
 */
bool timer_get_10Hz_timeout(void);

#endif // TIMER_H