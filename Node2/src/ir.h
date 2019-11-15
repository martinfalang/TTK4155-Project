#ifndef IR_H
#define IR_H

#include <stdbool.h>
#include "../../lib/inc/defines.h"

/**
 * @brief Initialize the IR module
 * 
 */
void ir_init(void);

/**
 * @brief Resets the IR beam. This resets the private variables that chech if 
 *        the beam is broken.
 * 
 */
void ir_reset(void);

/**
 * @brief Checks if the IR beam is broken
 * 
 * @return true The beam is broken
 * @return false The beam is not broken
 */
bool ir_beam_broken(void);

#if DEBUG
void ir_test(void);
#endif // DEBUG

#endif // IR_H