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
#include "sram-test.h"

void heart_beat()
{
  PORTA ^= 1 << PA0;
}

void test_uart()
{
  while (1)
  {
    heart_beat();
    uart_transmit('p');
    _delay_ms(500);
  }
}

int main(void)
{
  uart_init(); // So we can communicate with the terminal connected via JTAG
  SRAM_test(); // Test external RAM

  // DDRA |= 1 << DDA0;
}
