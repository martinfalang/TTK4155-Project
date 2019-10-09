#ifndef MCP2515_H
#define MCP2515_H

#include "mcp2515_defines.h"
#include <stddef.h>     // for size_t
#include "can_msg.h"
#include <stdint.h>

typedef struct mcp2515_can_msg {
    uint8_t sidh;
    uint8_t sidl;
    uint8_t eid8;    // not used
    uint8_t eid0;
    uint8_t dlc;  // dlc, length in 4 lower bits
    uint8_t data[8];
} mcp2515_can_msg_t;


void mcp2515_test_read(void);
void mcp2515_test_write(void);
void mcp2515_test_can(void);
void mcp_set_ops_mode(unsigned char state);

int mcp2515_init(unsigned char mode);

unsigned char mcp2515_read_byte(unsigned char address);
void mcp2515_read(unsigned char address, unsigned char *out_data, unsigned char out_data_length);
void mcp2515_write_byte(unsigned char address, unsigned char data);
void mcp2515_write(unsigned char start_address, unsigned char *data, size_t data_length);
void mcp2515_request_to_send(unsigned char command);
unsigned char mcp2515_read_status(void);
void mcp2515_bit_modify(unsigned char address, unsigned char mask_byte, unsigned char data);
void mcp2515_reset();


void mcp2515_can_convert_receive(can_msg_t* msg, const mcp2515_can_msg_t* canspi);
void mcp2515_can_convert_send(const can_msg_t* msg, mcp2515_can_msg_t* canspi);

#endif // MCP2515_H