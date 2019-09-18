
#include "mcp2515.h"
#include "spi.h"

#include <stdio.h>

void mcp2515_test(void) {
    
    char data = mcp2515_read();
    printf("MCP2515 status: %c\n", data);
}


unsigned char mcp2515_read(void) { // TODO: make this function more general
    spi_master_transmit(MCP2515_READ_STATUS);

    char data = spi_read();
    return data;
}

