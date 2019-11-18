
////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////

#include "dac.h"
#include "TWI_Master.h"

#include <avr/interrupt.h>  // sei()

////////////////////////////////////////////////////////////////////////////////
// Public functions
////////////////////////////////////////////////////////////////////////////////

void dac_init(void) {
    sei();
    TWI_Master_Initialise();
    dac_write(0, 0);
}


void dac_write(unsigned char level, int outn) {
    unsigned char buf[3];  // 0: slave addr, 1: cmd byte, 2: level
    buf[0] = DAC_SLAVE_ADDR;
    switch (outn) {
        case 1:
            buf[1] = DAC_OUT1_bm;
            break;
        case 2:
            buf[1] = DAC_OUT2_bm;
            break;
        case 3:
            buf[1] = DAC_OUT3_bm;
            break;
        case 0:
        default:
            buf[1] = DAC_OUT0_bm;
            break;
    }
    buf[2] = level;

    TWI_Start_Transceiver_With_Data(buf, 3);
}
