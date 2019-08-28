/**
  * Driver for communicating with the ATmega162 through UART
  */ 

void uart_init();

void send_char(char c);

char read_char();