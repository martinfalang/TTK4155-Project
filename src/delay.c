#include "delay.h"

#include "defines.h"
#include <util/delay.h>

void var_delay_ms(uint16_t ms) {
    while (ms--) {
        _delay_ms(1);
    }
}