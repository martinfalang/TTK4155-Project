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
#include "adc.h"

void heart_beat()
{
  PORTB ^= 1 << PB0;
}

int main(void)
{

  DDRB |= 1 << DDB0;
  
  SREG |= (1 << SREG_I);  // global interrupt enable
  uart_init(); // So we can communicate with the terminal connected via JTAG
  printf("Reset\n");
  xmem_init();
  //SRAM_test(); // Test external RAM

  adc_init();

  while(1) {
    heart_beat();
    uint8_t adc_data = adc_read(adc_channel_1);
    printf("ADC data: %i\n", adc_data);
    _delay_ms(100);
  }
}
