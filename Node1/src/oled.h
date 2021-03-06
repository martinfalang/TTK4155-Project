/**
 * @file oled.h
 * @author Kristian Brudeli
 *         Martin Falang
 *         Eirik Flemsæter Falck
 * @brief Implements drawing the screen buffer towards SSD1780 OLED driver 
 *        module. 
 * @version 0.1
 * @date 2019-11-18
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef OLED_H
#define OLED_H


////////////////////////////////////////////////////////////////////////////////
// Function declarations
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Initializes the OLED SSD1308 controller
 * 
 */
void oled_init(void);

/**
 * @brief Draws the buffer to the OLED screen
 * 
 * @param buffer pointer to oled buffer to print from
 */
void oled_draw_screen(uint8_t *buffer);


#endif /* OLED_H */