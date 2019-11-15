#ifndef CAN_H
#define CAN_H

#include "../../lib/inc/defines.h" // for DEBUG

#include <stdint.h>     // for uint
#include <stdbool.h>    // for bool

typedef struct can_msg {
    uint16_t sid;
    uint8_t length;
    uint8_t data[8];
} can_msg_t;

// General functions
/**
 * @brief Initialize the CAN bus
 * 
 * @param state 
 */
void can_init(unsigned char state);

// Get functions
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

// Send function
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