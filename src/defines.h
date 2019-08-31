// Defines and macros used in the project
#ifndef DEFINES_H
#define DEFINES_H

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

#define OLED_CMD_OFFSET 0x1000
#define OLED_DATA_OFFSET 0x1200
#define ADC_OFFSET 0x1400
#define SRAM_OFFSET 0x1800


#endif /* DEFINES_H */