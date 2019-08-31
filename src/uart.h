/**
  * Driver for communicating with the ATmega162 through UART
  */ 
#ifndef UART
#define UART

void uart_init(); // ubrr = uart baud rate register

void uart_transmit(char data);

char uart_receive();

#endif // UART