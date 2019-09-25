
#include "mcp2515.h"
#include "spi.h"

#include <stdio.h>

void mcp2515_test_read(void) {
    // Create buffer
    const unsigned char length = 1;
    unsigned char out_data[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    unsigned char start_address = 0x2A;

    mcp2515_read(start_address, out_data, length);

    // Print array
    for (int i = 0; i < length; i++) {
        printf("Read:\t%x\n", out_data[i]);
    }

}

void mcp2515_test_write(void) {
    // Create buffer
    const unsigned char length = 1;
    unsigned char out_data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    unsigned char start_address = 0x2A;

    mcp2515_write(start_address, out_data, length);

    // Print array
    for (int i = 0; i < length; i++) {
        printf("Wrote:\t%x\n", out_data[i]);
    }
}

void mcp2515_one_byte_write_test() {
    unsigned char data = 0x7F;
    unsigned char address = 0x29;

    spi_select();

    spi_write_byte(MCP2515_WRITE);
    spi_write_byte(address);
    spi_write_byte(data);

    spi_deselect();

    spi_select();
    spi_write_byte(MCP2515_READ);
    spi_write_byte(address);

    unsigned char out_data = spi_read_byte();

    spi_deselect();

    printf("Read byte:\t%x\n", out_data);
}

void mcp2515_read(unsigned char start_address, unsigned char *out_data, unsigned char out_data_length) {
    
    spi_select();

    // Initiate read
    spi_write_byte(MCP2515_READ);

    // Send address to start reading from
    spi_write_byte(start_address);

    printf("mcp_read(): out_data[0]:\t%x\n", out_data[0]);

    // Read into buffer
    for (unsigned char i = 0; i < out_data_length; i++) {
        out_data[i] = spi_read_byte();
    }

    printf("mcp_read(): out_data[0]:\t%x\n", out_data[0]);


    spi_deselect();
}

void mcp2515_write(unsigned char start_address, unsigned char *data, unsigned char data_length) {

    spi_select();

    // Initiate write
    spi_write_byte(MCP2515_WRITE);

    // Send address to start writing to
    spi_write_byte(start_address);

    // Write buffer to mcp2515
    for (unsigned char i = 0; i < data_length; i++) {
        spi_write_byte(data[i]);
    }

    spi_deselect();
}

