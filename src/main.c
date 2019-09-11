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
<<<<<<< HEAD
  PORTB ^= 1 << PB0;
=======
  PORTA ^= 1 << PA0;
>>>>>>> origin
}

void test_uart()
{
<<<<<<< HEAD
  printf("Hei\n");
=======
  uart_transmit('p');
>>>>>>> origin
}

int main(void)
{
<<<<<<< HEAD
  DDRB |= 1 << DDB0;
  
  uart_init(); // So we can communicate with the terminal connected via JTAG
  xmem_init();
  SRAM_test(); // Test external RAM
  while(1) {
    heart_beat();
    test_uart();
    _delay_ms(100);
=======
  fdevopen(uart_transmit, uart_receive); // Ask about compiler warnings
  uart_init();

  DDRA |= 1 << DDA0;

  while (1)
  {
    //heart_beat();
    //test_uart();

    // if (uart_recieve()) {
    //   heart_beat();
    // }
    printf("Hei på deg\n");

    _delay_ms(500);
>>>>>>> origin
  }
}
