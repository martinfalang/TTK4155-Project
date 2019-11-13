#ifndef ENCODER_H
#define ENCODER_H

#include <stdint.h>
#include <avr/io.h>


// MJ1
#define OE_  PH5  // active low indicated with suffix _
#define SEL  PH3  // 0: high byte    1: low byte
#define RST_ PH6

// MJ2
#define ENCODER_DATA_PORT PINK


void encoder_init(void);
int16_t encoder_read_raw(void);
uint8_t encoder_read_scaled(uint8_t lower, uint8_t upper);
void encoder_reset(void);


#endif  // ENCODER_H