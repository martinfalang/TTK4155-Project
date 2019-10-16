#include "defines.h"
#include <util/delay.h>

#include <stdio.h>
#include <avr/io.h>

#include "uart.h"
#include "heartbeat.h"


int main(void) {
    heartbeat_init();
    uart_init();

    while (1) {
        heartbeat();
        printf("Hello world!\n");
        _delay_ms(1000);
    }
}
