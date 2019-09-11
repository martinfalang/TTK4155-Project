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
#include <avr/interrupt.h>

#include "uart.h"
#include "sram-test.h"
#include "xmem.h"
#include "adc.h"


void heartbeat_init() {
  DDRB |= 1 << DDB0;
}

void heartbeat()
{
  PORTB ^= 1 << PB0;
}

int main(void)
{
  heartbeat_init();
  uart_init(); // So we can communicate with the terminal connected via JTAG
  xmem_init();
  adc_init();
  sei();  // set enable global interrupt flag
  printf("All inits ran successfully!\n");

  while(1) {
    _delay_ms(100);
    heartbeat();

    // uint8_t adc_data = adc_read(ADC_CH1);
    adc_start_conversion(ADC_CH1);
    uint8_t adc_data = adc_read();
    printf("ADC data: %i\n", adc_data);
  }
}
