/*
 * TestProject.c
 *
 * Created: 28.08.2019 12.19.50
 * Author : eirik
 */

#include "../../lib/inc/defines.h"

#include <stdio.h>

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>

#include "../../lib/inc/uart.h"
#include "xmem.h"
#include "adc.h"
#include "joystick.h"
#include "touch.h"
#include "../../lib/inc/mcp2515_defines.h"
#include "../../lib/inc/can.h"

void heartbeat_init() {
    DDRE |= 1 << DDE0;
}

void heartbeat()
{
    PORTE ^= 1 << PE0;
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
#if DEBUG
        // can_loopback_test();
        can_test_node_transmission();
#endif // DEBUG
    } 
}
