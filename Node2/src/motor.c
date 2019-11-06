#include "motor.h"
#include "dac.h"


void motor_init(void) {
    DDRH |= (1 << OE_) | (1 << SEL) | (1 << DIR) | (1 << RST) | (1 << EN);
    dac_init();

    motor_enable(1);
}


void motor_enable(int en) {
    if (en)
        PORTH |= (1 << EN);
    else
        PORTH &= ~(1 << EN);
}


void motor_set_dir(int dir) {
    if (dir)
        PORTH &= ~(1 << DIR);
    else
        PORTH |= (1 << DIR);
}


void motor_set_speed(int speed) {
    unsigned char level = speed * 2.55f;
    dac_write(level, 0);
}
