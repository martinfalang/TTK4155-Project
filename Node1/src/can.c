#include "can.h"
#include "defines.h"

#include <stdio.h>      // for printf()
#include <string.h>     // for memset
#include <util/delay.h> // for _delay_ms()
#include <avr/interrupt.h>

void can_test() {

    can_msg_t sendmsg = {
        .sid = 0x321,
        .length = 8,
        .data[0] = 9,
        .data[1] = 8,
        .data[2] = 7,
        .data[3] = 6,
        .data[4] = 5,
        .data[5] = 4,
        .data[6] = 3,
        .data[7] = 2,
    };

    sendmsg.sid = rand() % 256;
    sendmsg.length = rand() % 8;
    
    for (int i = 0; i  < 8; ++i) {
        sendmsg.data[i] = rand() % 256;
    }

    printf("Send: \n");
    can_print_msg(&sendmsg);

    can_send(&sendmsg);
    
    can_msg_t recvmsg;
    memset(&recvmsg, 0, sizeof(recvmsg));
    can_receive(&recvmsg);

    printf("Rec: \n");
    can_print_msg(&recvmsg);
    
    if (sendmsg.sid != recvmsg.sid) {
        printf("CAN loopback test failed\n");
        return;
    }
    if (sendmsg.length != recvmsg.length) {
        printf("CAN loopback test failed\n");
        return;
    }

    for (int i = 0; i < sendmsg.length; ++i) {
        if (sendmsg.data[i] != recvmsg.data[i]) {
            printf("CAN loopback test failed\n");
            return;
        }
    }

    printf("CAN test lookup passed\n");   
}



void can_test_node_transmission(void) {
    can_msg_t sendmsg = {
        .sid = 0,
        .length = 8,
        .data[0] = 3,
        .data[1] = 6,
        .data[2] = 3,
        .data[3] = 4,
        .data[4] = 3,
        .data[5] = 2,
        .data[6] = 1,
        .data[7] = 0
    };
    unsigned char val = mcp2515_read_byte(MCP_CANSTAT);
    unsigned char cur_mode = (val & MODE_MASK);

    printf("Current mode: 0x%.2x\n", cur_mode);

    printf("Send msg:\n");
    can_print_msg(&sendmsg);
    printf("\n\n");
    can_send(&sendmsg);
}


void can_init(unsigned char state) {
    mcp2515_init(state);

    // Turn off filters
    mcp2515_bit_modify(MCP_RXB0CTRL, 0x60, 0x60);   
}


void can_send(const can_msg_t* p_msg) {

    uint8_t sidl = p_msg->sid << 5;
    uint8_t sidh = p_msg->sid >> 3;

    mcp2515_write_byte(MCP_TXB0SIDL, sidl);
    mcp2515_write_byte(MCP_TXB0SIDH, sidh);

    mcp2515_write_byte(MCP_TXB0DLC, p_msg->length);

    for (int i = 0; i < p_msg->length; ++i) {
        mcp2515_write_byte(MCP_TXB0D0 + i, p_msg->data[i]);
    }

    mcp2515_request_to_send(MCP_RTS_TX0);
}


void can_receive(can_msg_t* outmsg) {
    
    uint8_t sidl = mcp2515_read_byte(MCP_RXB0SIDL);
    uint8_t sidh = mcp2515_read_byte(MCP_RXB0SIDH);

    outmsg->sid = sidh << 3 | sidl >> 5; 
    
    outmsg->length = mcp2515_read_byte(MCP_RXB0DLC) & 0xF;
    
    for (int i = 0; i < outmsg->length; ++i) {
        outmsg->data[i] = mcp2515_read_byte(MCP_RXB0D0 + i);
    }
}


void can_print_msg(const can_msg_t* msg) {
    // printf("MSG START\n");
    printf("ID: 0x%.4X\n", msg->sid);
    printf("Len: %d\n", msg->length);
    for (int i = 0; i < msg->length; ++i) {
        uint8_t d = msg->data[i];
        printf("Data%X: 0x%.2X\n", i, d);
    }
    // printf("MSG END\n");
}

