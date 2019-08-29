/*
 * TestProject.c
 *
 * Created: 28.08.2019 12.19.50
 * Author : eirik
 */

#define F_CPU 4915200

#include <avr/io.h>
#include <util/delay.h>

#include "uart.h"

void heart_beat() {
    PORTA ^= 1 << PA0;
}

void test_uart() {
     uart_transmit('p');
}

int main(void)
{
  uart_init();

  DDRA |= 1 << DDA0;

  while (1)
  {
    heart_beat();
    test_uart();
    _delay_ms(500);
    

  }
}
