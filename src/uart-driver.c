
// Situations to consider:
// The application tries to send a new character while the UART is busy transmitting the previous one
//   Solution: Wait until the UART is finished transmitting the previous one by reading the flag
// The application wants to be notified when a new character is received
//   Solution: Provide a callback function that is called each time a character is recieved

// TODO: Include header file defining macros?

#define FOSC 1843200 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC / 16 / BAUD - 1 // Baud rate register

void uart_init() // ubrr = uart baud rate register
{
    /** Initialize the uart unit */
    /* Set baud rate */
    UBRRH = (unsigned char)(MYUBRR >> 8); // high byte
    UBRRL = (unsigned char)(MYUBRR);      // low byte
    /* Enable receiver and transmitter */
    UCSRB = (1 << RXEN) | (1 << TXEN);
    /* Set frame format: 8data, 2stop bit */
    UCSRC = (1 << URSEL) | (1 << USBS) | (3 << UCSZ0);
}

void uart_transmit(char data)
{
    while (!(UCSRA & (1 << UDRE)))
        ; // Wait for transmit buffer to be empty

    UDR = data; // Put data in UDR - usart data register
}

char uart_recieve()
{
    while (!(UCSRA & (1 << RXC)))
        ; // Wait for data recieve
    
    return UDR; // Return the data in the data register
}