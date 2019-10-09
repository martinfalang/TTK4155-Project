#include "can.h"

#include <stdio.h>      // for printf()
#include <string.h>     // for memset
#include <stdbool.h>

typedef struct can_msg_spi{
    uint8_t sidh;
    uint8_t sidl;
    uint8_t eid8;    // not used
    uint8_t eid0;
    uint8_t dlc;  // dlc, length in 4 lower bits
    uint8_t data[8];
} can_msg_spi_t;

// Private function declaration
void _can_convert(can_msg_t* msg, can_msg_spi_t* canspi, bool receive);
void _print_bytes(unsigned char* p, size_t size);

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


void can_send(can_msg_t* p_msg) {
    can_msg_spi_t sendmsg;
    _can_convert(p_msg, &sendmsg, false);
    mcp2515_write(MCP_TXB0SIDH, (unsigned char *)&sendmsg, sizeof(sendmsg));
    mcp2515_request_to_send(MCP_RTS_TX0);
}


void can_recieve(can_msg_t* outmsg) {
    can_msg_spi_t recvmsg;
    mcp2515_read(MCP_TXB0SIDH, (unsigned char*)&recvmsg, sizeof(recvmsg));
    _can_convert(outmsg, &recvmsg, true);
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


void _can_convert(can_msg_t* msg, can_msg_spi_t* canspi, bool receive) {
    if (receive) {
        // when receiving
        // from can_msg_spi to can_msg
        msg->sid = (canspi->sidh << 8) | canspi->sidl;
        msg->length = canspi->dlc & 0xF;  // anding with 0xF because it's only the lower nibble that contains the length
        for (int i = 0; i < msg->length; ++i) {
            msg->data[i] = canspi->data[i];
        }
    }
    else {
        // when sending
        // from can_msg to can_msg_spi
        canspi->sidh = msg->sid >> 8;
        canspi->sidl = msg->sid & 0xFF;
        canspi->eid8 = 0;
        canspi->eid0 = 0;
        canspi->dlc  = msg->length & 0xF;
        for (int i = 0; i < msg->length; ++i) {
            canspi->data[i] = msg->data[i];
        }
    }
}


void _print_bytes(unsigned char* p, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        printf("Byte%d: 0x%.2X\n", i, p[i]);
    }
}

