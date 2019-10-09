#ifndef CAN_H
#define CAN_H

#include "mcp2515.h"
#include <stdint.h>


typedef struct can_msg {
    uint16_t sid;
    uint8_t length;
    uint8_t data[8];
} can_msg_t;

void can_test();

void can_init(unsigned char state);

void can_send(can_msg_t* p_msg);

void can_recieve(can_msg_t* outmsg);

void can_print_msg(const can_msg_t* msg);


#endif // CAN_H