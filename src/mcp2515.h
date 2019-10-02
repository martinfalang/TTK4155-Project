#ifndef MCP2515_H
#define MCP2515_H

// SPI instruction set
#define MCP2515_RESET           0b11000000
#define MCP2515_READ            0b00000011
#define MCP2515_READ_RX_BUFFER  0b10010000 // See datasheet for use
#define MCP2515_WRITE           0b00000010
#define MCP2515_LOAD_TX_BUFFER  0b01000000 // See datasheet for use
#define MCP2515_RTS             0b10000000 // Request-to-send
#define MCP2515_RTS_T0_bm       0b00000001
#define MCP2515_RTS_T1_bm       0b00000010
#define MCP2515_RTS_T2_bm       0b00000100
#define MCP2515_RTS_TXB2        0b0100
#define MCP2515_RTS_TXB1        0b0010
#define MCP2515_RTS_TXB0        0b0001
#define MCP2515_READ_STATUS     0b10100000
#define MCP2515_RX_STATUS       0b10110000
#define MCP2515_BIT_MODIFY      0b00000101

void mcp2515_test_read(void);
void mcp2515_test_write(void);

void mcp2515_read(unsigned char address, unsigned char *out_data, unsigned char out_data_length);
void mcp2515_write(unsigned char start_address, unsigned char *data, unsigned char data_length);
void mcp2515_request_to_send(unsigned char command);
unsigned char mcp2515_read_status(void);
void mcp2515_bit_modify(unsigned char address, unsigned char mask_byte, unsigned char data);
void mcp2515_reset();

#endif // MCP2515_H