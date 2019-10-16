#ifndef CAN_H
#define CAN_H

#include "mcp2515.h"
#include "can_msg.h"


void can_test();
void can_test_node_transmission(void);

void can_init(unsigned char state);

void can_send(const can_msg_t* p_msg);

void can_recieve(can_msg_t* outmsg);

void can_print_msg(const can_msg_t* msg);


#endif // CAN_H