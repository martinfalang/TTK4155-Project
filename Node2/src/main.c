
#include <stdio.h>
#include <avr/io.h>
#include "../../lib/inc/uart.h"

#include "../../lib/inc/defines.h"
#include <util/delay.h>

#include "../../lib/inc/spi.h"
#include "../../lib/inc/can.h"
#include "../../lib/inc/mcp2515_defines.h"


int main(void) {
    uart_init();

    //spi_init();
    can_init(MODE_NORMAL);

    printf("All inits ran successfully!\n");

    while (1) {
        const can_msg_t *recv_msg;

        if (can_new_msg()) {
            recv_msg = can_get_recv_msg();
            printf("\n\nRecv:\n");
            can_print_msg(recv_msg);
            can_send(recv_msg);
        }
        // _delay_ms(1);
    }
}
