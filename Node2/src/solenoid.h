#ifndef SOLENOID_H
#define SOLENOID_H

#include <avr/io.h>


#define SOLENOID_PIN PE5  // Pin 3 on the arduino s


/**
 * @brief Initializes the solenoid control pin
 * 
 */
void solenoid_init(void);

/**
 * @brief Gives a short pulse to the solenoid
 * 
 */
void solenoid_give_pulse(void);


#endif  // SOLENOID_H