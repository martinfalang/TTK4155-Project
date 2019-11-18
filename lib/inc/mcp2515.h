/**
 * @file mcp2515.h
 * @author Kristian Brudeli
 *         Martin Falang
 *         Eirik Flemsæter Falck
 * @brief Implements functions to use the MCP2515 CAN bus chip. 
 * @version 0.1
 * @date 2019-11-18
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef MCP2515_H
#define MCP2515_H

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////

#include "mcp2515_defines.h"
#include <stddef.h>             // for size_t

////////////////////////////////////////////////////////////////////////////////
// Function declarations
////////////////////////////////////////////////////////////////////////////////

// General functions
/**
 * @brief Initialize the MCP2515 CAN controller chip
 * 
 * @param mode Which mode to put the MCP2515 CAN controller chip in. See
 *             mcp2515_defines.h file for possbile modes. 
 */
void mcp2515_init(unsigned char mode);

/**
 * @brief Set the mode of operations on the MCP2515
 * 
 * @param mode Which mode to put the MCP2515 CAN controller chip in. See
 *             mcp2515_defines.h file for possbile modes. 
 */
void mcp_set_ops_mode(unsigned char mode);

/**
 * @brief Reset the MCP2515
 */
void mcp2515_reset();

// Read functions
/**
 * @brief Read one byte from given address in the MCP2015
 * 
 * @param address Address to read from
 * @return Byte read
 */
unsigned char mcp2515_read_byte(unsigned char address);

/**
 * @brief Reads multiple bytes from consequtive registers in the MCP2515
 * 
 * @param address Address to start reading from
 * @param out_data Pointer to the array to read the values into
 * @param out_data_length Number of bytes to read
 */
void mcp2515_read(unsigned char address, unsigned char *out_data, unsigned char out_data_length);

/**
 * @brief Reads the RX buffer on the
 * 
 * @param data Pointer to the array to read the values into
 * @param data_length Number of bytes to read
 */
void mcp2515_read_rx_buffer_data(unsigned char *data, unsigned char data_length);

/**
 * @brief Reads the status of the MCP2515
 * 
 * @return Status of the MCP2015
 */
unsigned char mcp2515_read_status(void);

// Write functions

/**
 * @brief Write a byte to a register in the MCP2515
 * 
 * @param address Address to write to
 * @param data Value to write
 */
void mcp2515_write_byte(unsigned char address, unsigned char data);

/**
 * @brief Write multiple bytes to consequtive registers in the MCP2515 
 * 
 * @param start_address Address to start writing to
 * @param data Pointer to the array of bytes to write
 * @param data_length Number of bytes to write
 */
void mcp2515_write(unsigned char start_address, unsigned char *data, size_t data_length);

/**
 * @brief Send request to send command to MCP2515
 * 
 * @param command Which TX buffer to send from. Must be on command format. See mcp2515_defines.h
 *                 for possible commands
 */
void mcp2515_request_to_send(unsigned char command);

/**
 * @brief Modify individual bits from registers in MCP2515
 * 
 * @param address Address to register to modify
 * @param mask_byte Mask of which bits should be modified
 * @param data Data to set the selected bits to
 */
void mcp2515_bit_modify(unsigned char address, unsigned char mask_byte, unsigned char data);

#endif // MCP2515_H