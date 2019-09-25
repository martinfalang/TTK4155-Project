#ifndef MCP2515_H
#define MCP2515_H

// SPI instruction set
#define MCP2515_RESET           0b11000000
#define MCP2515_READ            0b00000011
#define MCP2515_READ_RX_BUFFER  0b10010000 // See datasheet for use
#define MCP2515_WRITE           0b00000010
#define MCP2515_LOAD_TX_BUFFER  0b01000000 // See datasheet for use
#define MCP2515_RTS             0b10000000 // Request-to-send
#define MCP2515_RTS_TXB2        0b0100
#define MCP2515_RTS_TXB1        0b0010
#define MCP2515_RTS_TXB0        0b0001
#define MCP2515_READ_STATUS     0b10100000
#define MCP2515_RX_STATUS       0b10110000
#define MCP2515_BIT_MODIFY      0b00000101

void mcp2515_test(void);

#endif // MCP2515_H