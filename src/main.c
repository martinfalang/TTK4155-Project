/*
 * TestProject.c
 *
 * Created: 28.08.2019 12.19.50
 * Author : eirik
 */

#include "defines.h"

#include <avr/io.h>
#include <util/delay.h>

#include "uart.h"
#include "sram-test.h"

void heart_beat()
{
  PORTB ^= 1 << PB0;
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
  DDRB |= 1 << DDB0;
  uart_init(); // So we can communicate with the terminal connected via JTAG
  SRAM_test(); // Test external RAM
  while(1) {
    heart_beat();
    _delay_ms(100);
  }
}
