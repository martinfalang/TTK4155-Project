#ifndef PWM0_H
#define PWM0_H

#include <avr/io.h>
#include <stdint.h>

typedef enum pwm0_prescaler {
    PREOFF         = (1 << CS02) | (1 << CS01) | (1 << CS00),  // clock stopped
    PRE1        = (1 << CS00),  // prescaler = 1
    PRE8        = (1 << CS01),  // prescaler = 8
    PRE64       = (1 << CS00) | (1 << CS01),  // prescaler = 64
    PRE256      = (1 << CS02),  // prescaler = 256
    PRE1024     = (1 << CS02) | (1 << CS00)  // prescaler = 1024
} pwm0_prescaler_t;

void pwm0_init(pwm0_prescaler_t ps);

void pwm0_set_freq(uint16_t freq);

void pwm0_set_prescaler(pwm0_prescaler_t mode);

uint16_t pwm0_get_prescaler();

#endif /* PWM_H */