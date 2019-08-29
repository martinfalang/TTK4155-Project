/**
  * Driver for communicating with the ATmega162 through UART
  */ 

void uart_init(); // ubrr = uart baud rate register

void uart_transmit(char data);

char uart_recieve();
