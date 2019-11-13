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

typedef enum can_msg_type {
    CTRL_SID = 345, // Controller / joystick / slider data // TODO: Set actual value
    START_GAME_SID = 234, // TODO: Set actual value
    STOP_GAME_SID = 123 // TODO: Set actual value-
} can_msg_type_t;

// Definitions of messages corresponding to different message types 
typedef enum can_ctrl_msg_idx {
    JOY_DIR_IDX = 0,
    JOY_POS_X_IDX,
    JOY_POS_Y_IDX,
    BTNS_LEFT_IDX,
    BTNS_RIGHT_IDX,
    SLIDER_LEFT_IDX,
    SLIDER_RIGHT_IDX,
} can_ctrl_msg_idx_t;

// START_GAME has no fields, and therefore no corresponding struct

typedef enum can_sender {
    NODE1 = 1,
    NODE2 = 2
} can_sender_t;

typedef enum can_stop_game_msg {
    SENDER_IDX
} can_stop_game_msg_t;

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