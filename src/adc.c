#include <avr/interrupt.h>
#include "adc.h"


volatile uint8_t *adc = (uint8_t *) ADC_BASE;
volatile uint8_t adc_data = 0;

void adc_init() {
    // Setting Pin D2 (INTR) to input
    DDRD &= ~(1 << DDD2);
    // Enable pull up resistor
    PORTD |= (1 << PD2);
    


    // Trigger on falling edge
    MCUCR |= (1 << ISC01); 
    MCUCR &= ~(1 << ISC00);

    GICR |= (1 << INT0);  // Enable interrupt 0
}


void adc_start_conversion(adc_channel_t channel) {
    *adc = channel;
}


uint8_t adc_read() {
    return adc_data;
}

ISR(INT0_vect) {
    adc_data = *adc;
}
