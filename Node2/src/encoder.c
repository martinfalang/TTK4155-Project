#include "enocder.h"

#include "../../lib/inc/defines.h"
#include <util/delay.h>

// Values of encoder when far left and right
#define ENCODER_RIGHT       -8500
#define ENCODER_LEFT        -500

void encoder_init(void) {
    DDRH  |= (1 << OE_) | (1 << SEL) | (1 << RST_);
    PORTH |= (1 << RST_);  // reset the encoder to 0 when low, needs to be default high
    PORTH |= (1 << OE_);  // set output enable high to disable
    ENCODER_DATA_PORT = 0;  // set all port pins to input (0)
}


void encoder_reset(void) {
    PORTH &= ~(1 << RST_);
    _delay_us(20);
    PORTH |= (1 << RST_);
}


int16_t encoder_read_raw(void) {
    int16_t val = 0;
    PORTH &= ~(1 << OE_);  // enable output
    PORTH &= ~(1 << SEL);
    _delay_us(20);  // recommended to wait 20us before reading
    val = ENCODER_DATA_PORT << 8;
    PORTH |= (1 << SEL);
    _delay_us(20);  // recommended to wait 20us before reading
    val |= ENCODER_DATA_PORT;
    encoder_reset();
    PORTH |= (1 << OE_);

    return val;
}

uint8_t encoder_read_scaled(uint8_t lower, uint8_t upper) {
    int16_t val = encoder_read_raw();

    uint8_t res = (upper - lower) * (val - ENCODER_LEFT) / (ENCODER_RIGHT - ENCODER_LEFT);

    return res;

}