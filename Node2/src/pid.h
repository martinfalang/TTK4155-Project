#ifndef PID_H
#define PID_H

#include <stdint.h>


typedef struct pid_param {
    float Kp;  /** Proportional gain */
    float Ki;  /** Intergral gain */
    float Kd;  /** Derivative gain */
    float T;   /** Time step of discretization in ms */
    
    float measurement_raw;
    float measurement;
    float setpoint;

    float current_error;
    float previous_error;
    float cumulative_error;

    float output;
    float output_maximum;
    float output_minimum;
} pid_t;


/**
 * @brief Initializes the PID struct @p pid
 * 
 * @param pid Pointer to PID struct
 * @param kp Proportional gain
 * @param ki Intergral gain
 * @param kd Derivative gain
 * @param timestep Time step of discretization in ms in range [1, 250]
 * @param output_maximum Upper bound for the output of the PID controller in absolute value. -1 is no limiting.
 * @param output_minimum Lower bound for the output of the PID controller in absolute value. -1 is no lower bound. 
 */
void pid_init(pid_t *pid, float kp, float ki, float kd, float timestep, float output_maximum, float output_minimum);


/**
 * @brief Calculate the next output of the PID controller
 * 
 * @param pid Pointer to PID struct
 */
void pid_next_output(pid_t *pid);


/**
 * @brief Stops the PID timer (TIMER5)
 * 
 */
void pid_stop_timer(void);


/**
 * @brief Starts the PID timer (TIMER5)
 * 
 */
void pid_start_timer(void);


#endif  // PID_H