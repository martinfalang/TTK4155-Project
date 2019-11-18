#ifndef NODE_2_PWM
#define NODE_2_PWM

////////////////////////////////////////////////////////////////////////////////
// Function declarations
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Initialized the PWM for the servo motor
 * 
 */
void pwm_init(void);

/**
 * @brief Sets the correct duty cycle to achieve the desired @p degree .
 * 
 * @param degrees The degree to position the servo motor. Max range: [0, 180]
 */
void pwm_set_duty_cycle(int16_t degrees);

#endif /* NODE_2_PWM */