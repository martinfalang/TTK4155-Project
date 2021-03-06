/**
 * @file pid.h
 * @author Kristian Brudeli
 *         Martin Falang
 *         Eirik Flemsæter Falck
 * @brief Implements struct and functions for a PID controller. 
 * @version 0.1
 * @date 2019-11-18
 * 
 * @copyright Copyright (c) 2019
 * 
 */

/**
 * @brief Struct containing all PID parameters, measurements, setpoint, errors
 *        and output.
 *
 */
#ifndef PID_H
#define PID_H


////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>


////////////////////////////////////////////////////////////////////////////////
// Structs
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Struct containing all PID parameters, measurements, setpoint, errors
 *        and output.
 *
 */
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
    float error_deadzone;

    float output;
    float output_maximum;
    float output_minimum;
} pid_t;


////////////////////////////////////////////////////////////////////////////////
// Function declarations
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Initializes the PID struct @p pid with the given
 * 
 * @param pid Pointer to PID struct
 * @param kp Proportional gain
 * @param ki Intergral gain
 * @param kd Derivative gain
 * @param timestep Time step of discretization in ms in range [1, 250]
 * @param output_maximum Upper bound for the output of the PID controller in 
 *                       absolute value. -1 is no limiting.
 * @param output_minimum Lower bound for the output of the PID controller in 
 *                       absolute value. -1 is no lower bound. 
 * @param error_deadzone Minimum value the error have to be above for it to have 
 *                       an effect. The value is given i absolute value. -1 is 
 *                       no deadzone.
 */
void pid_init(pid_t *pid, float kp, float ki, float kd, float timestep, 
              float output_maximum, float output_minimum, float error_deadzone);


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
