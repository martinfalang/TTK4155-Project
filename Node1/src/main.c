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
#include "spi.h"
#include "mcp2515.h"
#include "can.h"

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
    joystick_init();
    touch_init();

    can_init(MODE_LOOPBACK);
    

    printf("All inits ran successfully!\n");

    // mcp2515_test_write();
    // mcp2515_test_read();

    // mcp2515_one_byte_write_test();

    while(1) {
        _delay_ms(1000);
        heartbeat();
        //can_test_node_transmission();
        can_test();
    } 
}
