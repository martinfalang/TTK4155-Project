#include "motor.h"
#include "dac.h"


void motor_init(void) {
    dac_init();

    // control pins
    DDRH |= (1 << DIR) | (1 << EN);

    motor_enable(1);
    motor_set_speed(0);
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
