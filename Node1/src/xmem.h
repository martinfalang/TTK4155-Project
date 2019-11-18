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
// Defines
////////////////////////////////////////////////////////////////////////////////

#define OLED_CMD_BASE               (uint8_t*)0x1000
#define OLED_CMD_SIZE               512
#define OLED_DATA_BASE              (uint8_t*)0x1200
#define OLED_DATA_SIZE              512
#define ADC_BASE                    (uint8_t*)0x1400
#define ADC_SIZE                    1024
#define SRAM_BASE                   (uint8_t*)0x1800
#define OLED_BUFFER_BASE            (SRAM_BASE)
#define OLED_BUFFER_SIZE            1024
#define OLED_MENU_ELEMENTS_BASE     (SRAM_BASE + OLED_BUFFER_SIZE)
#define SRAM_SIZE                   2048


////////////////////////////////////////////////////////////////////////////////
// Function declarations
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Initialize the use of external memory on ATmega162
 * 
 */
void xmem_init(void);

#endif /* XMEM_H */
