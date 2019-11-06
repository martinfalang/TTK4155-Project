#ifndef SOLENOID_H
#define SOLENOID_H

#include <avr/io.h>


#define SOLENOID_PIN PE5  // Pin 3 on the arduino s


void solenoid_init(void);
void solenoid_give_pulse(void);


#endif  // SOLENOID_H