/**
 * @file oled-buffer.h
 * @author Kristian Brudeli
 *         Martin Falang
 *         Eirik Flemsæter Falck
 * @brief Implements a buffer for the paged OLED screen on the USB 
 *        multi-function board P1000. 
 * @version 0.1
 * @date 2019-11-18
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef OLED_BUFFER_H
#define OLED_BUFFER_H

////////////////////////////////////////////////////////////////////////////////
// Defines
////////////////////////////////////////////////////////////////////////////////

#define OLED_WIDTH              128
#define OLED_HEIGHT             64
#define OLED_PAGES              8

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////


#include <stdbool.h>
#include <stdint.h>


////////////////////////////////////////////////////////////////////////////////
// Enums
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Font sizes for text. Fonts defined in "fonts.h"
 * 
 */
enum TEXT_SIZE
{
    SMALL = 4,
    MEDIUM = 5,
    LARGE = 8
};


////////////////////////////////////////////////////////////////////////////////
// Function declarations
////////////////////////////////////////////////////////////////////////////////

// Low level functions
/**
 * @brief Sets a single pixel in the buffer
 * 
 * @param x x-coordinate of pixel
 * @param y y-coordinate of pixel
 * @param val true to set pixel, false to clea
 * @param buffer pointer to oled buffer
 */
void oled_buffer_set_pixel(uint8_t x, uint8_t y, bool val, uint8_t *buffer);

/**
 * @brief Gets a 
 * 
 * @param x x-coordinate of pixel
 * @param y y-coordinate of pixel
 * @param buffer pointer to oled buffer
 * @return true pixel is set
 * @return false pixel is not set
 */
bool oled_buffer_get_pixel(uint8_t x, uint8_t y, uint8_t *buffer);

/**
 * @brief Sets a single column in a page, 8 horizontal pixels, at a time.
 * 
 * @param page page to set in
 * @param column horizontal column (x-coordinate) 
 * @param data 8-bit data, top bits first
 * @param buffer pointer to oled buffer
 */
void oled_buffer_set_page_column(int page, int column, uint8_t data, uint8_t *buffer);

/**
 * @brief Clears a whole page (8 bits tall) in the buffer
 * 
 * @param page vertical page to clear
 * @param buffer pointer to oled buffer
 */
void oled_buffer_clear_page(uint8_t page, uint8_t *buffer);

/**
 * @brief Clears all the pixels in the buffer
 * 
 * @param buffer pointer to oled buffer
 */
void oled_buffer_clear_screen(uint8_t *buffer);


/**
 * @brief Prints a single character to the buffer at the specified position
 * 
 * @param c character to print
 * @param size font size to use
 * @param page vertical page to print to
 * @param column horizontal position (x-coordinate) to print to
 * @param buffer pointer to oled buffer
 */
void oled_buffer_print_char(char c, enum TEXT_SIZE size, uint8_t page, uint8_t column, uint8_t *buffer);

/**
 * @brief Prints an entire c-string to the buffer, ended with '\0'
 * 
 * @param s string to print
 * @param size font size to use
 * @param page vertical page to print to
 * @param buffer 
 */
void oled_buffer_print_string(char *s, enum TEXT_SIZE size, uint8_t page, uint8_t *buffer);

// Drawing functions
/**
 * @brief Draws a line to the buffer
 * 
 * @param x_start start x-coordinate
 * @param y_start start y-coordinate
 * @param x_end end x-coordinate
 * @param y_end end y-coordinate
 * @param buffer pointer to oled buffer
 */
void oled_buffer_draw_line(uint8_t x_start, uint8_t y_start, uint8_t x_end, uint8_t y_end, uint8_t *buffer);

/**
 * @brief Draws a pictures split into pages of height 8. The split is the same
 *        way the OLED indexes its pages, see OLED documentation. 
 * 
 * @param columns Number of columns in picture
 * @param pages Number of pages (8 high) in picture
 * @param picture_P 2D array of picture in program memory (PROGMEM)
 * @param column_offset Which column to start drawing the picture on
 * @param page_offset Which page to start drawing the picture on
 * @param buffer Pointer to the buffer in which the picture should be drawn
 */
void oled_buffer_draw_picture(uint8_t columns, uint8_t pages, 
                              const uint8_t picture_P[pages][columns], 
                              uint8_t column_offset, uint8_t page_offset,
                              uint8_t *buffer);


#endif /* OLED_BUFFER_H */