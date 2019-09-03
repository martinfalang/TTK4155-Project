#include <avr/io.h>
#include "xmem.h"

void xmem_init(void) {
    // Enable sram in control register
    MCUCR |= (1 << SRE); // changes to alternate function for external memory pins
    SFIOR |= (1 << XMM2);  // masks out upper 4 bits of adress bus used by jtag
}
