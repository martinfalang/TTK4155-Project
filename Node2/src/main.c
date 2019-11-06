
#include <stdio.h>
#include <avr/io.h>
#include "../../lib/inc/uart.h"

#include "../../lib/inc/defines.h"
#include <util/delay.h>

#include "../inc/pid.h"


int main(void) {
    uart_init();
    
    pid_t motor_pid;
    pid_init(&motor_pid, 0, 0, 0, 250);

    printf("All inits ran successfully!\n");

    while (1) {
    }
}
