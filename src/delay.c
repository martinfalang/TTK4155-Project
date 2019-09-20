#include "delay.h"


void var_delay_ms(int ms) {
    while (ms--) {
        _delay_ms(1);
    }
}