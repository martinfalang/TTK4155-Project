#ifndef PID_H
#define PID_H

#include <stdint.h>


typedef struct pid_param {
    uint16_t Kp;  /** Proportional gain */
    uint16_t Ki;  /** Intergral gain */
    uint16_t Kd;  /** Derivative gain */
    uint16_t T;   /** Time step of discretization in ms */

    uint16_t current_error;
    uint16_t previous_error;
    uint16_t cumulative_error;

    uint16_t output;
} pid_t;


/**
 * @brief Initializes the PID struct @p pid
 * 
 * @param pid Pointer to PID struct
 * @param kp Proportional gain
 * @param ki Intergral gain
 * @param kd Derivative gain
 * @param timestep Time step of discretization in ms
 */
void pid_init(pid_t *pid, uint16_t kp, uint16_t ki, uint16_t kd, uint16_t timestep);


/**
 * @brief Calculate the next output of the PID controller
 * 
 * @param pid Pointer to PID struct
 * @param current Current value
 * @param setpoint Setpoint value
 * @return uint16_t Next output
 */
uint16_t pid_next(pid_t *pid, uint16_t current, uint16_t setpoint);


#endif  // PID_H