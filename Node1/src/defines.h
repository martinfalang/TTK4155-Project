// Defines and macros used in the project
#ifndef DEFINES_H
#define DEFINES_H

// Debug - set this to 1 to allow test functions
#define DEBUG 1

// Global
#define F_CPU 4915200 // Frequency of CPU.

// UART

#define FOSC 4915200 // Clock Speed
#define BAUD 9600
#define MYUBRR (FOSC / 16 / BAUD - 1) // Baud rate register

// SRAM and memory mapping:
/*
    MEMORY MAPPING: Based on the recommended memory mapping from the assignment p. 32
    0x1000 - 0x11FF: OLED command
    0x1200 - 0x13FF: OLED data
    0x1400 - 0x17FF: ADC
    0x1800 - 0x1FFF: SRAM
*/

// Sizes are in number of bytes
// BASE addresses are uint8_t* because each memory
// location contains 1 byte of data.
#define OLED_CMD_BASE (uint8_t*)0x1000
#define OLED_CMD_SIZE 512
#define OLED_DATA_BASE (uint8_t*)0x1200
#define OLED_DATA_SIZE 512
#define ADC_BASE    (uint8_t*)0x1400
#define ADC_SIZE    1024
#define SRAM_BASE   (uint8_t*)0x1800
#define SRAM_SIZE   2048


#endif /* DEFINES_H */