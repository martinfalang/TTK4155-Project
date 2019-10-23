#ifndef MCP2515_H
#define MCP2515_H

#include "mcp2515_defines.h"
#include <stddef.h>     // for size_t
#include <stdint.h>
#include <stdbool.h>    // for bool


// General functions
void mcp2515_init(unsigned char mode);
void mcp_set_ops_mode(unsigned char mode);
void mcp2515_reset();

// Read functions
unsigned char mcp2515_read_byte(unsigned char address);
void mcp2515_read(unsigned char address, unsigned char *out_data, unsigned char out_data_length);
void mcp2515_read_rx_buffer_data(unsigned char *data, unsigned char data_length);
unsigned char mcp2515_read_status(void);

// Write functions
void mcp2515_write_byte(unsigned char address, unsigned char data);
void mcp2515_write(unsigned char start_address, unsigned char *data, size_t data_length);
void mcp2515_request_to_send(unsigned char command);
void mcp2515_bit_modify(unsigned char address, unsigned char mask_byte, unsigned char data);

#endif // MCP2515_H