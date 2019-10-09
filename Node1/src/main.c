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
// #include "spi.h"
// #include "mcp2515.h"
// #include "can.h"
#include "oled.h"
#include "oled-buffer.h"
#include "oled-menu.h"
#include "sram-test.h"
#include "timer.h"

void heartbeat_init()
{
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
    joystick_init();
    touch_init();

    // SRAM_test();

    // spi_init();
    // _delay_ms(10);
    //mcp2515_init(MODE_LOOPBACK);

    // can_init(MODE_LOOPBACK);

    // mcp2515_test_write();
    // mcp2515_test_read();

    oled_menu_init(OLED_BUFFER_BASE);
    timer_init(); // Interrupt timer
    printf("All inits ran successfully!\n");

    while (1)
    {
        if (oled_menu_should_update())
        {
            printf("Oled menu should update");
            oled_menu_update(OLED_BUFFER_BASE);
        }
    }

    // mcp2515_one_byte_write_test();

    // while (1)
    // {
    //     heartbeat();
    //     //mcp2515_test_can();
    //     // can_test();
    //     _delay_ms(1000);
    // }
}
