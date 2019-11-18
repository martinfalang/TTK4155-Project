/**
 * @file heartbeat.h
 * @author Kristian Brudeli
 *         Martin Falang
 *         Eirik Flemsæter Falck
 * @brief Implements functions for toggling a heartbeat LED. 
 * @version 0.1
 * @date 2019-11-18
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef HEARTBEAT_H
#define HEARTBEAT_H

////////////////////////////////////////////////////////////////////////////////
// Function declarations
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Initialize the heartbeat LED
 * 
 */
void heartbeat_init(void);

/**
 * @brief Toggles the heartbeat LED
 * 
 */
void heartbeat(void);


#endif  // HEARTBEAT_H