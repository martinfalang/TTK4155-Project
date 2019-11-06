
#include <stdio.h>
#include <avr/io.h>
#include "../../lib/inc/uart.h"

#include "../../lib/inc/defines.h"
#include <util/delay.h>

#include "../../lib/inc/spi.h"
#include "../../lib/inc/can.h"
#include "../../lib/inc/mcp2515_defines.h"

#include "ir.h"

#include "motor.h"
#include "enocder.h"



int main(void) {
    uart_init();
    motor_init();
    encoder_init();    
    can_init(MODE_NORMAL);
    printf("All inits ran successfully!\n");

    while (1) {
        int16_t enc = encoder_read();
        printf("Encoder value: %d\n", enc);

        _delay_ms(10);
    }
}
