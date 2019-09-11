#ifndef ADC_H
#define ADC_H

#include <stdint.h>
#include <avr/io.h>

#define EXT_ADC ((uint8_t*)ADC_BASE)
#define INTR    PD2
#define WR      PE0
#define RD      PE2
#define CH1_bm  0b0100



void adc_init();

void adc_start_read();

uint8_t adc_read();



#endif /* ADC_H */