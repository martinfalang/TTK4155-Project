#ifndef CAN_MSG_H
#define CAN_MSG_H


#include <stdint.h>

// This file exists only to avoid circular dependecies.

typedef struct can_msg {
    uint16_t sid;
    uint8_t length;
    uint8_t data[8];
} can_msg_t;


#endif  // CAN_MSG_H