
#include "../inc/mcp2515.h"
#include "../inc/spi.h"
#include "../inc/defines.h"

#include <util/delay.h>

#if DEBUG
#include <stdio.h>
#endif // DEBUG

void mcp2515_init(unsigned char mode) {

    spi_init();
    
    mcp2515_reset();

#if DEBUG
    unsigned char val = mcp2515_read_byte(MCP_CANSTAT);
    unsigned char cur_mode = (val & MODE_MASK);

    if (cur_mode != MODE_CONFIG) {
        printf("mcp_init(): Mode not config after reset, mode was: 0x%.2x\n", cur_mode);
    }
#endif // DEBUG

    // Enable interrupts on RX0 buffer
    mcp2515_bit_modify(MCP_CANINTE, MCP_RX0IF, MCP_RX0IF);

    mcp_set_ops_mode(mode);

#if DEBUG
    val = mcp2515_read_byte(MCP_CANSTAT);
    cur_mode = (val & MODE_MASK);
    if (cur_mode != mode) {
        printf("mcp_init(): Mode was not set to selected mode 0x%x. Mode was: 0x%x\n", mode, cur_mode);
    }
#endif // DEBUG
}

void mcp_set_ops_mode(unsigned char mode) {
    mcp2515_bit_modify(MCP_CANCTRL, MODE_MASK, mode);
}

void mcp2515_reset() {

    spi_slave_select();

    spi_write_byte(MCP_RESET);

    spi_slave_deselect();
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

    spi_write_byte(MCP_READ);

    spi_write_byte(start_address);

    for (unsigned char i = 0; i < out_data_length; i++) {
        out_data[i] = spi_read_byte();
    }

    spi_slave_deselect();
}


void mcp2515_read_rx_buffer_data(unsigned char *data, unsigned char data_length) {

    spi_slave_select();

    spi_write_byte(MCP_READ_RX0_D0);

    for (unsigned char i = 0; i < data_length; ++i) {
        data[i] = spi_read_byte();
    }

    spi_slave_deselect();
} 

unsigned char mcp2515_read_status(void) {

    spi_slave_select();

    spi_write_byte(MCP_READ_STATUS);

    unsigned char status = spi_read_byte();

    spi_slave_deselect();

    return status;
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

    spi_write_byte(MCP_WRITE);

    spi_write_byte(start_address);

    for (unsigned char i = 0; i < data_length; i++) {
        spi_write_byte(data[i]);
    }

    spi_slave_deselect();
}

void mcp2515_request_to_send(unsigned char command) {

    spi_slave_select();

    spi_write_byte(command);

    spi_slave_deselect();
}

void mcp2515_bit_modify(unsigned char address, unsigned char mask_byte, unsigned char data) {

    spi_slave_select();

    spi_write_byte(MCP_BITMOD);

    spi_write_byte(address);

    spi_write_byte(mask_byte);

    spi_write_byte(data);

    spi_slave_deselect();
}
