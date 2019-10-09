
#include "mcp2515.h"
#include "spi.h"
#include "defines.h"

#include <util/delay.h>

#include <stdio.h>

int mcp2515_init(unsigned char mode) {
    mcp2515_reset();

    unsigned char val = mcp2515_read_byte(MCP_CANSTAT);
    unsigned char cur_mode = (val & MODE_MASK);

    if (cur_mode != MODE_CONFIG) {
        printf("mcp_init(): Mode not config after reset, mode was: %x\n", mode);
        return 0;
    }

    // Set mode
    mcp_set_ops_mode(mode);

    val = mcp2515_read_byte(MCP_CANSTAT);
    cur_mode = (val & MODE_MASK);

    if (cur_mode != mode) {
        printf("mcp_init(): Mode was not set to selected mode %x. Mode was: %x", mode, cur_mode);
        return 0;
    }

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

    _delay_ms(1);
}



void mcp2515_can_convert_receive(can_msg_t* msg, const mcp2515_can_msg_t* canspi) {
    // when receiving
    // from can_msg_spi to can_msg
    msg->sid = (canspi->sidh << 8) | canspi->sidl;
    msg->length = canspi->dlc & 0xF;  // anding with 0xF because it's only the lower nibble that contains the length
    for (int i = 0; i < msg->length; ++i) {
        msg->data[i] = canspi->data[i];
    }
}

void mcp2515_can_convert_send(const can_msg_t* msg, mcp2515_can_msg_t* canspi) {
    // when sending
    // from can_msg to can_msg_spi
    canspi->sidh = msg->sid >> 8;
    canspi->sidl = msg->sid & 0xFF;
    canspi->eid8 = 0;
    canspi->eid0 = 0;
    canspi->dlc  = msg->length & 0xF;
    for (int i = 0; i < msg->length; ++i) {
        canspi->data[i] = msg->data[i];
    }
}