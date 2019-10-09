#include "can.h"


typedef struct can_msg_spi{
    uint8_t  ctrl;
    uint8_t sidh;
    uint8_t sidl;
    uint8_t eid8;    // not used
    uint8_t eid0;
    uint8_t  length;  // dlc, only 4 lower bits
    uint8_t  data[8];
} can_msg_spi_t;


void can_init() {
    // Set can in loopback mode
    mcp_set_ops_mode(MODE_LOOPBACK);
}


void can_send(const can_msg_t* p_msg) {
    mcp2515_write(MCP_TXB0CTRL, (unsigned char *)p_msg, sizeof(*p_msg));
}


void can_recieve(can_msg_t* outmsg) {
    can_msg_spi_t recvmsg;
    mcp2515_read(MCP_RXB0CTRL, (unsigned char*)&recvmsg, sizeof(recvmsg));
    _can_convert(outmsg, &recvmsg);
}

void _can_convert(can_msg_t* outmsg, can_msg_spi_t* canspi) {
    outmsg->sid = (canspi->sidh << 8) | canspi->sidl;
    outmsg->eid = (canspi->eid8 << 8) | canspi->eid0;
    outmsg->length = canspi->length;
    for (int i = 0; i < outmsg->length; ++i) {
        outmsg->data[i] = canspi->data[i];
    }
}