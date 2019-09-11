/*
 * TestProject.c
 *
 * Created: 28.08.2019 12.19.50
 * Author : eirik
 */

#include "defines.h"

#include <stdio.h>

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "uart.h"
#include "sram-test.h"
#include "xmem.h"

void heart_beat()
{
  PORTB ^= 1 << PB0;
}

void test_uart()
{
  printf("Hei\n");
}

int main(void)
{
  DDRB |= 1 << DDB0;
  
  uart_init(); // So we can communicate with the terminal connected via JTAG
  xmem_init();
  SRAM_test(); // Test external RAM
  while(1) {
    heart_beat();
    test_uart();
    _delay_ms(100);
  }
}
