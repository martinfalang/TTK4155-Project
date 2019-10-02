#include "can.h"



void can_init() {
    // do something, idk
}


void can_send(const can_msg_t* p_msg) {
    // TODO: change to use whatever buffer you want
    // TODO: Find out whats up with these macros. Why there is none for TXBSIDH 
    
    //mcp2515_write_byte(txb0sidh, p_msg->id & 0x07);
    //mcp2515_write_byte(txb0sidl, p_msg->id & 0xFF);
}


can_msg_t can_recieve() {
    
}

