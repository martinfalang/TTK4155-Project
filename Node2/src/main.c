#include <stdio.h>
#include <avr/io.h>
#include "uart.h"

#include "defines.h"
#include <util/delay.h>

#include "pwm.h"

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

    pwm_init();

    int16_t degs = -40;

    while(1) {
        heartbeat();
        _delay_ms(200);

        printf("%d", degs);
        pwm_set_duty_cycle(degs);
        degs += 10;

        if (degs > 250) {degs = -40;}
    }

    // while (1) {
    //     heartbeat();
	//     printf("Hello world!!!\n");
    //     _delay_ms(1000);
    // }
}
