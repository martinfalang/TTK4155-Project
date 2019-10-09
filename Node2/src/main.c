
#include <stdio.h>
#include <avr/io.h>
#include "uart.h"

#include "defines.h"
#include <util/delay.h>

#include "spi.h"
#include "can.h"


int main(void) {
    uart_init();

    //spi_init();
    //can_init(MODE_LOOPBACK);

    printf("All inits ran successfully!\n");

    while (1) {
	    printf("Hello world!\n");
        
        can_test();

        _delay_ms(1000);
    }
}
