
#include <stdio.h>
#include <avr/io.h>
#include "../../lib/inc/uart.h"

#include "../../lib/inc/defines.h"
#include <util/delay.h>

#include "../inc/pid.h"

#include "ir.h"

#include "motor.h"
#include "enocder.h"
#include "solenoid.h"



int main(void) {
    uart_init();
<<<<<<< HEAD
    motor_init();
    encoder_init();    
    solenoid_init();
    can_init(MODE_NORMAL);
=======
    
    pid_t motor_pid;
    pid_init(&motor_pid, 0, 0, 0, 250);

>>>>>>> node2-pi-controller
    printf("All inits ran successfully!\n");

    _delay_ms(100);
    solenoid_give_pulse();

    while (1) {
<<<<<<< HEAD
        
        _delay_ms(10);
=======
>>>>>>> node2-pi-controller
    }
}
