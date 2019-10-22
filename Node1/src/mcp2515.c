
#include "mcp2515.h"
#include "spi.h"
#include "defines.h"

#include <util/delay.h>

#include <stdio.h>

int mcp2515_init(unsigned char mode) {

    spi_init();
    
    mcp2515_reset();

    unsigned char val = mcp2515_read_byte(MCP_CANSTAT);
    unsigned char cur_mode = (val & MODE_MASK);

    // printf("Val: 0x%.2x cur_mode: 0x%.2x\n", val, cur_mode);
    if (cur_mode != MODE_CONFIG) {
        // TODO: Find out why it does not go into config mode after reset
        printf("mcp_init(): Mode not config after reset, mode was: 0x%.2x\n", cur_mode);
        //return 0;
    }

    // Enable interrupts on RX0 buffer
    mcp2515_bit_modify(MCP_CANINTE, MCP_RX0IF, MCP_RX0IF);
    // _delay_us(100);
    // Set mode
    mcp_set_ops_mode(mode);

    val = mcp2515_read_byte(MCP_CANSTAT);
    cur_mode = (val & MODE_MASK);
    // printf("Current mode: %.2x\n", cur_mode);
    if (cur_mode != mode) {
        printf("mcp_init(): Mode was not set to selected mode 0x%x. Mode was: 0x%x\n", mode, cur_mode);
        //return 0;
    }

    unsigned char filters = mcp2515_read_byte(MCP_RXB1CTRL);
    printf("The filter was: %.2x\n", filters);

    return 1;

}

void mcp_set_ops_mode(unsigned char state) {
    mcp2515_bit_modify(MCP_CANCTRL, MODE_MASK, state);
}

unsigned char mcp2515_read_byte(unsigned char address) {
    unsigned char res;

    spi_slave_select();
    spi_write_byte(MCP_READ);
    spi_write_byte(address);
    res = spi_read_byte();
    spi_slave_deselect();
    return res;    
}

void mcp2515_read(unsigned char start_address, unsigned char *out_data, unsigned char out_data_length) {
    
    spi_slave_select();

    // Initiate read
    spi_write_byte(MCP_READ);

    // Send address to start reading from
    spi_write_byte(start_address);

    // Read into buffer
    for (unsigned char i = 0; i < out_data_length; i++) {
        out_data[i] = spi_read_byte();
    }

    spi_slave_deselect();
}

void mcp2515_write_byte(unsigned char address, unsigned char data) {
    spi_slave_select();
    spi_write_byte(MCP_WRITE);
    spi_write_byte(address);
    spi_write_byte(data);
    spi_slave_deselect();
}

void mcp2515_write(unsigned char start_address, unsigned char *data, size_t data_length) {

    spi_slave_select();

    // Initiate write
    spi_write_byte(MCP_WRITE);

    // Send address to start writing to
    spi_write_byte(start_address);

    // Write buffer to mcp2515
    for (unsigned char i = 0; i < data_length; i++) {
        spi_write_byte(data[i]);
    }

    spi_slave_deselect();
}

void mcp2515_request_to_send(unsigned char command) {

    spi_slave_select();

    // Send RTS command byte
    spi_write_byte(command);

    spi_slave_deselect();
}

unsigned char mcp2515_read_status(void) {

    spi_slave_select();

    // Send command
    spi_write_byte(MCP_READ_STATUS);

    // Receive status
    unsigned char status = spi_read_byte();

    spi_slave_deselect();

    return status;
}

unsigned char mcp2515_read_rx_status(void) {

    spi_slave_select();

    spi_write_byte(MCP_RX_STATUS);

    unsigned char status = spi_read_byte();

    spi_slave_deselect();

    return status;
}

void mcp2515_bit_modify(unsigned char address, unsigned char mask_byte, unsigned char data) {

    spi_slave_select();

    // Command
    spi_write_byte(MCP_BITMOD);

    // Send address
    spi_write_byte(address);

    // Send the mask byte
    spi_write_byte(mask_byte);

    // Change the chosen bits to data
    spi_write_byte(data);

    spi_slave_deselect();
}

void mcp2515_reset() {

    spi_slave_select();

    spi_write_byte(MCP_RESET);

    spi_slave_deselect();

    _delay_us(100);
}

void mcp2515_read_rx_buffer_data(unsigned char *data, unsigned char data_length) {

    spi_slave_select();

    spi_write_byte(MCP_READ_RX0_D0);

    for (unsigned char i = 0; i < data_length; ++i) {
        data[i] = spi_read_byte();
    }

    spi_slave_deselect();
} 
