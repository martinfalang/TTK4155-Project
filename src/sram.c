#include <avr/io.h>
#include "sram.h"

void sram_init(void) {
    // Enable sram in control register
    MCUCR |= (1 << SRE); // NOT TESTED YET
    SFIOR |= (1 << XMM0); 
}
