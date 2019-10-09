#ifndef CAN_H
#define CAN_H

#include "mcp2515.h"
#include <stdint.h>


typedef struct can_msg {
    uint16_t sid;
    uint16_t eid;
    uint8_t length;
    uint8_t data[8];
} can_msg_t;

void can_init();

void can_send(const can_msg_t* p_msg);

void can_recieve(can_msg_t* outmsg);


#endif // CAN_H