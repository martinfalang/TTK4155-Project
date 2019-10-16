
#include <stdio.h>
#include <avr/io.h>
#include "heartbeat.h"
#include "uart.h"

#include "defines.h"
#include <util/delay.h>

#include "spi.h"
#include "can.h"


int main(void) {
    heartbeat_init();
    uart_init();

    can_init(MODE_LOOPBACK);

    printf("All inits ran successfully!\n");

    while (1) {
        heartbeat();
        printf("Hello world!\n");
        _delay_ms(1000);
    }
}
