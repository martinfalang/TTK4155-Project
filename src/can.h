#ifndef CAN_H
#define CAN_H

#include "mcp2515.h"
#include <stdint.h>

typedef struct can_msg {
    uint16_t id;
    uint8_t length;  // only 4 lower bits
    uint8_t data[8];
} can_msg_t;

void can_init();

void can_send(const can_msg_t* p_msg);

can_msg_t can_recieve();





#endif // CAN_H