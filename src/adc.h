#ifndef ADC_H
#define ADC_H

#include <stdint.h>
#include <avr/io.h>
#include "defines.h"


typedef enum adc_ch {
    ADC_CH1 = 0b0100,
    ADC_CH2 = 0b0101,
    ADC_CH3 = 0b0110,
    ADC_CH4 = 0b0111
} adc_channel_t;


void adc_init();

void adc_start_conversion(adc_channel_t channel);

uint8_t adc_read();


#endif /* ADC_H */