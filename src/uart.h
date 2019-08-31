/**
  * Driver for communicating with the ATmega162 through UART
  */ 

#ifndef UART_H
#define UART_H

void uart_init(); // ubrr = uart baud rate register

void uart_transmit(char data);

char uart_recieve();

#endif /* UART_H */