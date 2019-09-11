/**
  * Driver for communicating with the ATmega162 through UART
  */ 

#ifndef UART_H
#define UART_H

#include <stdio.h>

void uart_init(); // ubrr = uart baud rate register

int uart_transmit(char data, FILE *f);

int uart_recieve(FILE *f);

extern FILE *uart;

#endif /* UART_H */