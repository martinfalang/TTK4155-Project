#include "adc.h"
#include "defines.h"



void adc_init() {
    // Setting Pin D2 (INTR) to input
    DDRD &= ~(1 << DDD2);
    // Enable pull up resistor
    PORTD |= (1 << PD2);
    
    // Trigger falling edge
    MCUCR |= (1 << ISC01); 
    MCUCR &= ~(1 << ISC00);

    // Enable interrupt 0, this crashes the entire thing so i feel like its wrong :-) 
    //GICR |= (1 << INT0);
    
}


uint8_t adc_read(uint8_t channel) {
    
    volatile uint8_t *adc = (uint8_t *) EXT_ADC;
    
    *adc = channel;
    
    return *adc;
}