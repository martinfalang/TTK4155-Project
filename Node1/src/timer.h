#ifndef TIMER_H
#define TIMER_H

////////////////////////////////////////////////////////////////////////////////
// Inclues
////////////////////////////////////////////////////////////////////////////////

#include <stdbool.h>

////////////////////////////////////////////////////////////////////////////////
// Defines
////////////////////////////////////////////////////////////////////////////////

// Flash heartbeat with 1 Hz
#define HEARTBEAT_FREQ      60

// Send joystick with 10 Hz
#define CAN_FREQ            6

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
bool timer_get_oled_timeout(void);

/**
 * @brief Checks if the heartbeat timer has timed out and should toggle the LED
 * 
 * @return true Has timed out
 * @return false Has not timed out
 */
bool timer_get_heartbeat_timeout(void);

/**
 * @brief Check if the CAN timer has timed out and should send a CAN message
 * 
 * @return true Has timed out
 * @return false Has not timed out
 */
bool timer_get_can_timeout(void);

#endif // TIMER_H