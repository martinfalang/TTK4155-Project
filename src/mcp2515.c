
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

void mcp2515_read(unsigned char start_address, unsigned char *out_data, unsigned char out_data_length) {
    
    spi_select();

    // Initiate read
    spi_write_byte(MCP2515_READ);

    // Send address to start reading from
    spi_write_byte(start_address);

    // Read into buffer
    for (unsigned char i = 0; i < out_data_length; i++) {
        out_data[i] = spi_read_byte();
    }

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

void mcp2515_request_to_send(unsigned char command) {

    spi_select();

    // Send RTS command byte
    spi_write_byte(command);

    spi_deselect();
}

unsigned char mcp2515_read_status(void) {

    spi_select();

    // Send command
    spi_write_byte(MCP2515_READ_STATUS);

    // Receive status
    unsigned char status = spi_read_byte();

    spi_deselect();

    return status;
}

void mcp2515_bit_modify(unsigned char address, unsigned char mask_byte, unsigned char data) {

    spi_select();

    // Command
    spi_write_byte(MCP2515_BIT_MODIFY);

    // Send address
    spi_write_byte(address);

    // Send the mask byte
    spi_write_byte(mask_byte);

    // Change the chosen bits to data
    spi_write_byte(data);

    spi_deselect();
}

void mcp2515_reset() {

    spi_select();

    spi_write_byte(MCP2515_RESET);

    spi_deselect();
}