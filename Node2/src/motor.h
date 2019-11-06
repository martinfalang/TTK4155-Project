#ifndef MOTOR_H
#define MOTOR_H

#include <avr/io.h>

// MJ1
#define OE_ PH5  // active low indicated with suffix _
#define SEL PH3
#define DIR PH1
#define RST PH6
#define EN  PH4

// MJ2
#define DO0 PK0
#define DO1 PK1
#define DO2 PK2
#define DO3 PK3
#define DO4 PK4
#define DO5 PK5
#define DO6 PK6
#define DO7 PK7



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