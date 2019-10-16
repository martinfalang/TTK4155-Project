#ifndef MCP2515_H
#define MCP2515_H

#include "mcp2515_defines.h"
#include <stddef.h>     // for size_t
#include <stdint.h>

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
unsigned char mcp2515_read_rx_status(void);

#endif // MCP2515_H