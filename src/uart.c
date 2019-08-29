#ifndef UART_DRIVER
#define UART_DRIVER

#include <avr/io.h>
#include "uart.h"

// TODO: Include header file defining macros?

#define FOSC 4915200 // Clock Speed
#define BAUD 9600
#define MYUBRR (FOSC / 16 / BAUD - 1) // Baud rate register

void uart_init() // ubrr = uart baud rate register
{
    /** Initialize the uart unit */
    /* Set baud rate */
    UBRR0H = (unsigned char)(MYUBRR >> 8); // high byte
    UBRR0L = (unsigned char)(MYUBRR);      // low byte
    /* Enable receiver and transmitter */
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    /* Set frame format: 8data, 2stop bit */
    UCSR0C = (1 << URSEL0) | (1 << USBS0) | (3 << UCSZ00);
}

void uart_transmit(char data)
{
    /** Transmit one char of data to the mcu */
    while (!(UCSR0A & (1 << UDRE0)))
        ; // Wait for transmit buffer to be empty

    UDR0 = data; // Put data in UDR - usart data register
}

char uart_recieve()
{
    /** Recieve one char of data from the mcu */
    while (!(UCSR0A & (1 << RXC0)))
        ; // Wait for data recieve
    
    return UDR0; // Return the data in the data register
}
#endif /* UART_DRIVER */