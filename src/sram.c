#include <avr/io.h>

void sram_init(void) {
    // Enable sram in control register
    MCUCR |= (1 << SRE); // NOT TESTED YET



}
