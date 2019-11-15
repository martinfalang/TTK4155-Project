// Defines and macros used in the project
#ifndef DEFINES_H
#define DEFINES_H

// Debug - set this to 1 to allow test functions
#define DEBUG                   0
#define COMPILE_SRAM_TEST       0
#define COMPILE_TOUCH_TEST      0
#define COMPILE_JOYSTICK_TEST   0
#define COMPILE_CAN_TEST        0

// Global CPU frequency
#if defined (__AVR_ATmega162__)
    #define F_CPU 4915200
#elif defined (__AVR_ATmega2560__)
    #define F_CPU 16000000
#else
    #define F_CPU 0
#endif

// UART

//#define FOSC 4915200 // Clock Speed
#define BAUD 9600
#define MYUBRR (F_CPU / 16 / BAUD - 1) // Baud rate register

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
#define OLED_BUFFER_BASE (SRAM_BASE)
#define SRAM_SIZE   2048

// OLED
#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define OLED_PAGES 8

#define OLED_BUFFER_SIZE (OLED_WIDTH * OLED_HEIGHT)

#endif /* DEFINES_H */