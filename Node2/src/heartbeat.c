#include "heartbeat.h"
#include <avr/io.h>

#define HEARTBEAT_DDR  DDRB
#define HEARTBEAT_PORT PORTB
#define HEARTBEAT_PIN  PB7


void heartbeat_init(void) {
    HEARTBEAT_DDR |= 1 << HEARTBEAT_PIN;
}

void heartbeat(void)
{
    HEARTBEAT_PORT ^= 1 << HEARTBEAT_PIN;
}