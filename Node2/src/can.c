#include "can.h"
#include "defines.h"

#include <stdio.h>      // for printf()
#include <string.h>     // for memset
#include <util/delay.h> // for _delay_ms()

void can_test() {

    can_msg_t sendmsg = {
        .sid = 0x123,
        .length = 8,
        .data[0] = 9,
        .data[1] = 9,
        .data[2] = 5,
        .data[3] = 4,
        .data[4] = 3,
        .data[5] = 2,
        .data[6] = 1,
        .data[7] = 0
    };

    printf("Send msg:\n");
    can_print_msg(&sendmsg);
    printf("\n\n");
    can_send(&sendmsg);
    
    _delay_ms(1);
    printf("RX status: %.2x\n", mcp2515_read_rx_status());
    
    unsigned char rxb0 = mcp2515_read_byte(MCP_RXB0CTRL);
    unsigned char rxb1 = mcp2515_read_byte(MCP_RXB1CTRL);

    printf("rxb0ctrl: 0x%.2x \trxb1ctrl: %#.2x\n", rxb0, rxb1);

    can_msg_t recvmsg;
    memset(&recvmsg, 0, sizeof(recvmsg));
    recvmsg.length = 8;
    can_recieve(&recvmsg);

    printf("Received msg:\n");
    can_print_msg(&recvmsg);    
    printf("\n\n");    
}


void can_test_node_reception(void) {
    can_msg_t recvmsg;
    memset(&recvmsg, 0, sizeof(recvmsg));
    can_recieve(&recvmsg);
    printf("RX status: 0x%.2x\n", mcp2515_read_rx_status());

    printf("Received msg:\n");
    can_print_msg(&recvmsg);
}


void can_init(unsigned char state) {
    mcp2515_init(state);

    // Turn off filters
    mcp2515_bit_modify(MCP_RXB0CTRL, 0x60, 0x60);
    mcp2515_bit_modify(MCP_RXB1CTRL, 0x60, 0x60);
}


void can_send(const can_msg_t* p_msg) {
    mcp2515_can_msg_t sendmsg;
    mcp2515_can_convert_send(p_msg, &sendmsg);
    mcp2515_write(MCP_TXB0SIDH, (unsigned char *)&sendmsg, sizeof(sendmsg));
    mcp2515_request_to_send(MCP_RTS_TX0);
}


void can_recieve(can_msg_t* outmsg) {
    mcp2515_can_msg_t recvmsg;
    mcp2515_read(MCP_RXB0SIDH, (unsigned char*)&recvmsg, sizeof(recvmsg));
    mcp2515_can_convert_receive(outmsg, &recvmsg);

    // // printf("mcp2515_can_msg_t raw\n");
    // for (int i = 0; i < sizeof(recvmsg); ++i) {
    //     printf("byte%d\t0x%.2X\n", i, ((uint8_t*)&recvmsg)[i]);
    // }
}


void can_print_msg(const can_msg_t* msg) {
    // printf("MSG START\n");
    printf("ID: 0x%.4X\n", msg->sid);
    printf("Len: %d\n", msg->length);
    for (int i = 0; i < msg->length; ++i) {
        uint8_t d = msg->data[i];
        printf("D%X: 0x%.2X\n", i, d);
    }
    // printf("MSG END\n");
}

