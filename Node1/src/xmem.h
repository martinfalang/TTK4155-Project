/**
 * @file xmem.h
 * @author Kristian Brudeli
 *         Martin Falang
 *         Eirik Flemsæter Falck
 * @brief Implements initialization function for external memory on the 
 *        ATmega162 microcontroller. 
 * @version 0.1
 * @date 2019-11-18
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef XMEM_H
#define XMEM_H

////////////////////////////////////////////////////////////////////////////////
// Function declarations
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Initialize the use of external memory on ATmega162
 * 
 */
void xmem_init(void);

#endif /* XMEM_H */