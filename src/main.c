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
#include "xmem.h"
#include "adc.h"
#include "joystick.h"
#include "touch.h"
#include "oled-buffer.h"
#include "oled.h"

void heartbeat_init()
{
  DDRB |= 1 << DDB0;
}

void heartbeat()
{
  PORTB ^= 1 << PB0;
}

void oled_test_screen_2(void)
{
  uint8_t *buffer = OLED_BUFFER_BASE;
  oled_buffer_clear(buffer);
  // Try to write a string

  oled_print_string("fdas", 4, MEDIUM, 4, buffer);
  // oled_draw_line(10, 10, 20, 10, buffer);
  

  // Print buffer to screen
  oled_draw_screen(buffer);
}

int main(void)
{
  heartbeat_init();
  uart_init(); // So we can communicate with the terminal connected via JTAG
  xmem_init();
  adc_init();
  joystick_init();
  touch_init();
  oled_init();

  printf("All inits ran successfully!\n");

  oled_test_screen_2();

  while (1)
  {
    heartbeat();
    _delay_ms(100);
  }
}
