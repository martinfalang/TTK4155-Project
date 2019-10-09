
    #include <stdio.h>
#include <avr/io.h>
#include "uart.h"

#include "defines.h"
#include <util/delay.h>

#include "spi.h"
#include "can.h"

void heartbeat_init() {
    DDRB |= 1 << DDB7;
}

void heartbeat()
{
    PORTB ^= 1 << PB7;
}


int main(void) {
    heartbeat_init();
    uart_init();

    spi_init();
    can_init(MODE_LOOPBACK);

    while (1) {
        heartbeat();
	    printf("Hello world!\n");
        can_test();
        _delay_ms(1000);
    }
}
