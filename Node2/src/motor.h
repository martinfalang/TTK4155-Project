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
 * @brief Sets speed of motor. A speed of @c +100 is full speed in one 
 *        direction, @c -100 is full speed the other direction. 
 * 
 * @param speed Speed from @c -100 to @c 100
 */
void motor_set_speed(int speed);



#endif  // MOTOR_H