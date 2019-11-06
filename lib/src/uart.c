#include <avr/io.h>
#include <stdio.h>

#include "../inc/defines.h"
#include "../inc/uart.h"

FILE *uart;

#if defined (__AVR_ATmega162__)
    #define FRAME_FORMAT    (1 << URSEL0) | (1 << USBS0) | (3 << UCSZ00)
#elif defined (__AVR_ATmega2560__)
    #define FRAME_FORMAT    (1 << USBS0) | (3 << UCSZ00)
#endif

void uart_init() // ubrr = uart baud rate register
{
    /** Initialize the uart unit */
    /* Set baud rate */
    UBRR0H = (unsigned char)(MYUBRR >> 8); // high byte
    UBRR0L = (unsigned char)(MYUBRR);      // low byte
    /* Enable receiver and transmitter */
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    /* Set frame format: 8data, 2stop bit */
    UCSR0C = FRAME_FORMAT;

    uart = fdevopen(&uart_transmit, &uart_recieve);
}

int uart_transmit(char data, FILE *f) 
{
    //Including FILE *f to not get compiler warnings
    /** Transmit one char of data to the mcu */
    while (!(UCSR0A & (1 << UDRE0)))
        ; // Wait for transmit buffer to be empty

    UDR0 = data; // Put data in UDR - usart data register

    return data; //Return data only to not get compiler warnings
}

int uart_recieve(FILE *f)
{
    //Including FILE *f to not get compiler warnings
    /** Recieve one char of data from the mcu */
    while (!(UCSR0A & (1 << RXC0)))
        ; // Wait for data recieve

    return UDR0; // Return the data in the data register
}