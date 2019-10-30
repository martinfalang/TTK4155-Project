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

    int16_t degs = 90;
    pwm_set_duty_cycle(degs);

    int16_t delta_degs = 1;

    while(1) {
        heartbeat();
        _delay_ms(20);

        printf("%d\n", degs);
        pwm_set_duty_cycle(degs);
        degs += delta_degs;

        if (degs > 180) { delta_degs = -1;}
        if (degs < 0) { delta_degs = 1; }
    }

    // while (1) {
    //     heartbeat();
	//     printf("Hello world!!!\n");
    //     _delay_ms(1000);
    // }
}
