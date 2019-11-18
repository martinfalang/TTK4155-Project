/**
 * @file pwm0.h
 * @author Kristian Brudeli
 *         Martin Falang
 *         Eirik Flemsæter Falck
 * @brief Implements functions for setting the frequency and prescaler of timer0
 *        on the ATmega162 microcontroller. This is used with the buzzer. 
 * @version 0.1
 * @date 2019-11-18
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef PWM0_H
#define PWM0_H


////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////

#include <avr/io.h>
#include <stdint.h>


////////////////////////////////////////////////////////////////////////////////
// Enums
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Defines possible prescaler bit masks
 * 
 */
typedef enum pwm0_prescaler {
    PREOFF      = ~((1 << CS02) | (1 << CS01) | (1 << CS00)),  // clock stopped
    PRE1        = (1 << CS00),  // prescaler = 1
    PRE8        = (1 << CS01),  // prescaler = 8
    PRE64       = (1 << CS00) | (1 << CS01),  // prescaler = 64
    PRE256      = (1 << CS02),  // prescaler = 256
    PRE1024     = (1 << CS02) | (1 << CS00)  // prescaler = 1024
} pwm0_prescaler_t;


////////////////////////////////////////////////////////////////////////////////
// Public functions
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Initializes timer0 in CTC PWM mode
 * 
 */
void pwm0_init();

/**
 * @brief Sets the frequency of the output signal. Duty cycle is fixed at 50%. 
 *        This functions sets the prescaler to a fitting value. 
 * 
 * @param freq The desired frequency
 */
void pwm0_set_freq(uint16_t freq);

/**
 * @brief Sets the prescaler to @p mode
 * 
 * @param mode Which prescaler from @c pwm0_prescaler_t to use. 
 */
void pwm0_set_prescaler(pwm0_prescaler_t mode);

/**
 * @brief Gets the currently used prescaler
 * 
 * @return uint16_t Which prescaler is used
 */
uint16_t pwm0_get_prescaler();

/**
 * @brief Stops timer0 from running, i.e. stopping the PWM output. 
 * 
 */
void pwm0_stop(void);


#endif /* PWM_H */
