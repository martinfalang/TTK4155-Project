
#include "mcp2515.h"
#include "spi.h"

#include <stdio.h>

void mcp2515_test(void) {
    spi_select();

    spi_write_byte(MCP2515_READ_RX_BUFFER);

    unsigned char data = spi_read_byte();

    spi_deselect();

    printf("MCP2515 status: %x\n", data);

    
}


