#include "enocder.h"

#include "../../lib/inc/defines.h"
#include <util/delay.h>
#include <stdio.h>

// these initial values seemed to work fine during testing
static int16_t encoder_left = -500;
static int16_t encoder_right = -8500;

#define ENCODER_CALIBRATE_BTN_PIN PK0

void encoder_init(void) {
    DDRH  |= (1 << OE_) | (1 << SEL) | (1 << RST_);
    PORTH |= (1 << RST_);  // reset the encoder to 0 when low, needs to be default high
    PORTH |= (1 << OE_);  // set output enable high to disable
    ENCODER_DATA_PORT = 0;  // set all port pins to input (0)

    // Calibrate button
    DDRK &= ~(1 << ENCODER_CALIBRATE_BTN_PIN);  // set at input
    PORTK |= (1 << ENCODER_CALIBRATE_BTN_PIN);  // enable internal pull-up

    encoder_reset();
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

float encoder_scale_measurement(float val, int16_t lower, int16_t upper) {
    
    float res = ((val - encoder_left) / (encoder_right - encoder_left)) 
                * (upper - lower) + lower;

    // if (res >= upper)
    //     return upper;
    // else if (res <= lower)
    //     return lower;
    // else
        
    return res;
}


void encoder_calibrate(void) {
    printf("Disconnect power to motor. Press button when complete...");
    while (PINK & (1 << ENCODER_CALIBRATE_BTN_PIN));  // wait for button press
    printf(" OK\n");
    _delay_ms(500);  // wait for button to be released


    printf("Move carriage to the far left and press button...");
    while (PINK & (1 << ENCODER_CALIBRATE_BTN_PIN));  // wait for button press
    encoder_left = 0;
    encoder_reset();
    printf(" OK\n");
    _delay_ms(1000);  // wait for button to be released

    printf("Move carriage to the far right and press button...");
    int16_t pos = 0;
    while (PINK & (1 << ENCODER_CALIBRATE_BTN_PIN)) {
        pos += encoder_read_raw();
        _delay_ms(100);
    }  // wait for button press
    encoder_right = pos;
    printf(" OK: %d\n", encoder_right);
    _delay_ms(1000);

    printf("Move carriage to the far left and press button...");
    encoder_reset();
    while (PINK & (1 << ENCODER_CALIBRATE_BTN_PIN)) {
        pos += encoder_read_raw();
        _delay_ms(100);
    }  // wait for button press
    encoder_left = pos;
    printf(" OK: %d\n", encoder_left);

    printf("Reconnect power to motor. Pres button when complete...");
    while (PINK & (1 << ENCODER_CALIBRATE_BTN_PIN));  // wait for button press
    printf(" OK\n");
    _delay_ms(500);  // wait for button to be released


    printf("Calibration complete\n");
}

