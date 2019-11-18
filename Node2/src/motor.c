
////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////

#include "motor.h"
#include "dac.h"

////////////////////////////////////////////////////////////////////////////////
// Public functions
////////////////////////////////////////////////////////////////////////////////

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
    static const int neg_dir = 1;  // 0 or 1: the direction of travel when speed is negative
    if (speed < 0) {
        motor_set_dir(neg_dir);
        speed *= -1;
    }
    else {
        motor_set_dir(!neg_dir);
    }
    
    if (speed > MOTOR_MAX_INPUT)
        speed = MOTOR_MAX_INPUT;

    dac_write(speed, 0);
}
