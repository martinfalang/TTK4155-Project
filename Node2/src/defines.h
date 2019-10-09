// Defines and macros used in the project
#ifndef DEFINES_H
#define DEFINES_H


// Global
#define F_CPU 16000000UL // Frequency of CPU.


// UART
#define FOSC 16000000UL // Clock Speed
#define BAUD 9600
#define MYUBRR (FOSC / 16 / BAUD - 1) // Baud rate register


#endif /* DEFINES_H */