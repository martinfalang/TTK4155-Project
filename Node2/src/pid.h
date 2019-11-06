#ifndef PID_H
#define PID_H

#include <stdint.h>


typedef struct pid_param {
    int16_t Kp;  /** Proportional gain */
    int16_t Ki;  /** Intergral gain */
    int16_t Kd;  /** Derivative gain */
    int16_t T;   /** Time step of discretization in ms */
    
    int16_t measurement;
    int16_t setpoint;

    int16_t current_error;
    int16_t previous_error;
    int16_t cumulative_error;

    int16_t output;
} pid_t;


/**
 * @brief Initializes the PID struct @p pid
 * 
 * @param pid Pointer to PID struct
 * @param kp Proportional gain
 * @param ki Intergral gain
 * @param kd Derivative gain
 * @param timestep Time step of discretization in ms in range [1, 250]
 */
void pid_init(pid_t *pid, int16_t kp, int16_t ki, int16_t kd, int16_t timestep);


/**
 * @brief Calculate the next output of the PID controller
 * 
 * @param pid Pointer to PID struct
 */
void pid_next_output(pid_t *pid);


#endif  // PID_H