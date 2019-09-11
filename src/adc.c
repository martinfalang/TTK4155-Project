#include <util/delay.h>
#include "adc.h"
#include "defines.h"


void adc_init() {
    // ensure CS is pulled low by GAL
    // PORTC |= 1 << 3;
    // PORTC &= ~(1 << 4);
    *EXT_ADC;
    
    // set PA0-3 according to MUX table
    uint8_t porta_temp = PORTA;  // store current state
    PORTA = CH1_bm;
    
    // keep RD high
    PORTE |= (1 << RD);
    
    // set WR low
    PORTE &= ~(1 << WR);
    
    // wait tDS = 100 ns
    _delay_us(100);

    // write WR high
    PORTE |= 1 << WR;
    
    // CH1 is now selected
    PORTA = porta_temp;  // necessary?? 
}



void adc_start_read() {
    // ensure CS is pulled low by GAL
    // write WR and RD low
    // INTR is reset high
    // wait until INTR is pulled low by AD
    //      can be done by interrupt or polling
    // new data is now ready
    // can adc_read() to extract data from data bus
}


uint8_t adc_read() {
    // read data from data bus

    return *EXT_ADC;  // correct???
}