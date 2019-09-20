#ifndef DELAY_H
#define DELAY_H

#include <util/delay.h>

void var_delay_ms(int ms) {
    while (ms--) {
        _delay_ms(1);
    }
}


#endif // DELAY_H