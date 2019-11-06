
#include <stdio.h>
#include <avr/io.h>
#include "../../lib/inc/uart.h"

#include "../../lib/inc/defines.h"
#include <util/delay.h>
#include "../../lib/inc/mcp2515_defines.h"
#include "../../lib/inc/can.h"

#include "../inc/pid.h"

#include "ir.h"

#include "motor.h"
#include "enocder.h"
#include "solenoid.h"



int main(void) {
    uart_init();
    motor_init();
    encoder_init();    
    solenoid_init();
    can_init(MODE_NORMAL);
    printf("All inits ran successfully!\n");

    _delay_ms(100);
    solenoid_give_pulse();

    while (1) {
        
        _delay_ms(10);
    }
}
