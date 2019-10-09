#include "adc.h"


volatile uint8_t *adc = (uint8_t *) ADC_BASE;

void adc_init() {
    // Setting Pin D2 (INTR) to input
    DDRD &= ~(1 << DDD2);
    // Enable pull up resistor
    PORTD |= (1 << PD2);
}


uint8_t adc_read(adc_channel_t channel) {
    // decided against using interrupts because polling gave
    // a cleaner interface. 

    *adc = channel;
    while (PIND & (1<<PD2));  // wait for conversion to finish
    return *adc;
}
