#ifndef ENCODER_H
#define ENCODER_H

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <avr/io.h>

////////////////////////////////////////////////////////////////////////////////
// Defines
////////////////////////////////////////////////////////////////////////////////

// MJ1
#define OE_  PH5  // active low indicated with suffix _
#define SEL  PH3  // 0: high byte    1: low byte
#define RST_ PH6

// MJ2
#define ENCODER_DATA_PORT PINK

////////////////////////////////////////////////////////////////////////////////
// Function declarations
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Initialize the encoder pins 
 * 
 */
void encoder_init(void);

/**
 * @brief Read the raw value of the encoder. This resets the encoder so the 
 *        returned value is the *change* from last reading
 * 
 * @return int16_t The signed change in encoder position
 */
int16_t encoder_read_raw(void);

/**
 * @brief Scales the (absolute) measurement/position of the encoder so it better
 *        matches the position reference
 * 
 * @param val The value to scale (i.e. the sum of raw encoder values)
 * @param lower The lower bound of the output
 * @param upper The upper bound of the output
 * @return float The scaled position (returned as float to match the PID better)
 */
float encoder_scale_measurement(float val, int16_t lower, int16_t upper);

/**
 * @brief Reset the encoder value to 0
 * 
 */
void encoder_reset(void);

/**
 * @brief Calibrate routine for the encoder
 * 
 */
void encoder_calibrate(void);


#endif  // ENCODER_H