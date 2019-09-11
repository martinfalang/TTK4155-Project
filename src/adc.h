#ifndef ADC_H
#define ADC_H

#include <stdint.h>
#include <avr/io.h>

#define EXT_ADC ADC_BASE
#define INTR    PD2

#define adc_channel_1 (uint8_t)(0b0100)
#define adc_channel_2 (uint8_t)(0b0101)
#define adc_channel_3 (uint8_t)(0b0110)
#define adc_channel_4 (uint8_t)(0b0111)

typedef enum adc_ch {
    ADC_CH1 = 0b0100,
    ADC_CH2 = 0b0101,
    ADC_CH3 = 0b0110,
    ADC_CH4 = 0b0111
} adc_channel_t;

void adc_init();

void adc_start_read();

uint8_t adc_read(uint8_t channel);



#endif /* ADC_H */