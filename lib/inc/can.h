/**
 * @file can.h
 * @author Kristian Brudeli
 *         Martin Falang
 *         Eirik Flemsæter Falck
 * @brief Implement CAN bus functions. 
 * @version 0.1
 * @date 2019-11-18
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef CAN_H
#define CAN_H

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////

#include "../../lib/inc/defines.h"

#include <stdint.h>
#include <stdbool.h>    

////////////////////////////////////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////////////////////////////////////

typedef struct can_msg {
    uint16_t sid;
    uint8_t length;
    uint8_t data[8];
} can_msg_t;

////////////////////////////////////////////////////////////////////////////////
// Function declarations
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Initialize the CAN bus
 * 
 * @param state 
 */
void can_init(unsigned char state);

/**
 * @brief Checks if a new CAN message is ready
 * 
 * @return true A new CAN message is ready
 * @return false No new CAN message is ready
 */
bool can_new_msg(void);

/**
 * @brief Gets the data of the received message
 * 
 * @return const can_msg_t* A const pointer to the message data
 */
const can_msg_t *can_get_recv_msg(void);

/**
 * @brief Send a CAN message
 * 
 * @param p_msg 
 */
void can_send(const can_msg_t* p_msg);

// Test functions
#if COMPILE_CAN_TEST
void can_loopback_test();
void can_test_node_transmission(void);
void can_print_msg(const can_msg_t* msg);
#endif // COMPILE_CAN_TEST

#endif // CAN_H