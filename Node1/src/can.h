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
void can_test_node_transmission(void);

void can_init(unsigned char state);

void can_send(const can_msg_t* p_msg);

void can_receive(void);

void can_print_msg(const can_msg_t* msg);

const can_msg_t *can_get_recv_msg(void);
bool can_new_msg(void);

#endif // CAN_H