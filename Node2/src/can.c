#include "can.h"

#include <stdio.h>      // for printf()
#include <string.h>     // for memset


void can_test() {

    can_msg_t sendmsg = {
        .sid = 0,
        .length = 8,
        .data[0] = 0,
        .data[1] = 1,
        .data[2] = 2,
        .data[3] = 3,
        .data[4] = 4,
        .data[5] = 5,
        .data[6] = 6,
        .data[7] = 7
    };

    printf("Send msg:\n");
    can_print_msg(&sendmsg);
    printf("\n\n");
    can_send(&sendmsg);
    
    can_msg_t recvmsg;
    memset(&recvmsg, 0, sizeof(recvmsg));
    recvmsg.length = 8;
    can_recieve(&recvmsg);

    printf("Received msg:\n");
    can_print_msg(&recvmsg);    
    printf("\n\n");
    
}


void can_init(unsigned char state) {
    // Set can in loopback mode
    mcp2515_init(state);
}


void can_send(const can_msg_t* p_msg) {
    mcp2515_can_msg_t sendmsg;
    mcp2515_can_convert_send(p_msg, &sendmsg);
    mcp2515_write(MCP_TXB0SIDH, (unsigned char *)&sendmsg, sizeof(sendmsg));
    mcp2515_request_to_send(MCP_RTS_TX0);
}


void can_recieve(can_msg_t* outmsg) {
    mcp2515_can_msg_t recvmsg;
    mcp2515_read(MCP_TXB0SIDH, (unsigned char*)&recvmsg, sizeof(recvmsg));
    mcp2515_can_convert_receive(outmsg, &recvmsg);
}


void can_print_msg(const can_msg_t* msg) {
    printf("MSG START\n");
    printf("ID: 0x%.4X\n", msg->sid);
    printf("Len: %d\n", msg->length);
    for (int i = 0; i < msg->length; ++i) {
        uint8_t d = msg->data[i];
        printf("Data%X: 0x%.2X\n", i, d);
    }
    printf("MSG END\n");
}

