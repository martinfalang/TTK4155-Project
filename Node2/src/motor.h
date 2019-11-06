#ifndef MOTOR_H
#define MOTOR_H

#include <avr/io.h>

// MJ1
#define DIR PH1
#define EN  PH4


void motor_init(void);
void motor_enable(int en);
void motor_set_dir(int dir);
/**
 * @brief Sets speed of motor by setting the duty cycle of the PWM signal
 * 
 * @param speed Duty cycle from 0 to 100
 */
void motor_set_speed(int speed);



#endif  // MOTOR_H