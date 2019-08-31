#include <avr/io.h>


/*
    MEMORY MAPPING: Based on the recommended memory mapping from the assignment p. 32
    0x1000 - 0x11FF: OLED command
    0x1200 - 0x13FF: OLED data
    0x1400 - 0x17FF: ADC
    0x1800 - 0x1FFF: SRAM
*/

// Memory offsets
#define OLED_CMD_OFFSET 0x1000
#define OLED_DATA_OFFSET 0x1200
#define ADC_OFFSET 0x1400
#define SRAM_OFFSET 0x1800

void sram_init(void) {
    // Enable sram in control register
    MCUCR |= (1 << SRE); // NOT TESTED YET



}
