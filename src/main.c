/*
 * TestProject.c
 *
 * Created: 28.08.2019 12.19.50
 * Author : eirik
 */

#define F_CPU 4915200

#include <avr/io.h>
#include <util/delay.h>

#include "uart-driver.h"

int main(void)
{
  uart_init();

  DDRA |= 1 << DDA0;

  while (1)
  {
    uart_transmit('o');
    _delay_ms(500);
    PORTA ^= 1 << PA0;
  }
}
