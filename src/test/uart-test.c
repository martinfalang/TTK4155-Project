#ifndef UART_TEST
#define UART_TEST

#include "uart-test.h"
#include "../uart-driver.h"

void test_uart()
{
    // Puts the mcu in our "test mode"
    // which puts it in an infinite loop that returns the
    // data sent to it over UART

    uart_init();

    unsigned char recieved = "";

    while (1)
    {
        recieved = uart_recieve();
        uart_transmit(recieved);
    }
}

#endif /* UART_TEST */