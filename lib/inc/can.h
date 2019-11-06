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
void can_init(unsigned char state);

// Get functions
bool can_new_msg(void);
const can_msg_t *can_get_recv_msg(void);

// Send function
void can_send(const can_msg_t* p_msg);

// Test functions
#if COMPILE_CAN_TEST
void can_loopback_test();
void can_test_node_transmission(void);
void can_print_msg(const can_msg_t* msg);
#endif // COMPILE_CAN_TEST

#endif // CAN_H