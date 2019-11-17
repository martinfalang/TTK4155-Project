
////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include <avr/pgmspace.h>

#include "oled-buffer.h"
#include "../../lib/inc/defines.h"
#include "fonts.h"

/*
    About buffer memory mapping:
    The buffer is written in a way minimize the amount of operations needed to update the screen .
    
    The indexes are arranged such that it is an array of 8 bit unsigned integers, 
    stacked horizontally, such that each uint8 represents the column of one page in memory.

    This means that the indexing is in turn given by:

        index = page * num_columns + x

    Where page is given by the
        
        page = y / num_pages  // Implicitly floored

*/

////////////////////////////////////////////////////////////////////////////////
// Public functions
////////////////////////////////////////////////////////////////////////////////

uint16_t oled_buffer_get_index(uint8_t x, uint8_t y)
{
    return (y / OLED_PAGES) * OLED_WIDTH + x; // Calculate index corresponding to x, y in buffer array
}

void oled_buffer_set_pixel(uint8_t x, uint8_t y, bool val, uint8_t *buffer)
{
    int index = oled_buffer_get_index(x, y);

    if (val)
    {
        buffer[index] |= (1 << (y % 8)); // Set the bit at the given position
    }
    else
    {
        buffer[index] &= !(1 << (y % 8)); // Clear the bit at the given position
    }
}

void oled_buffer_set_page_column(int page, int column, uint8_t data, uint8_t *buffer)
{
    buffer[page * OLED_WIDTH + column] = data;
}

bool oled_buffer_get_pixel(uint8_t x, uint8_t y, uint8_t *buffer)
{
    return (bool)((1 << (y % 8)) & buffer[oled_buffer_get_index(x, y)]); // Mask out the relevant bit
}

void oled_buffer_clear_page(uint8_t page, uint8_t *buffer)
{
    for (uint8_t col = 0; col < OLED_WIDTH; ++col)
    {
        oled_buffer_set_page_column(page, col, 0, buffer);
    }
}

void oled_buffer_clear_screen(uint8_t *buffer)
{
    for (uint8_t p = 0; p < OLED_PAGES; ++p)
    {
        oled_buffer_clear_page(p, buffer);
    }
}

void oled_buffer_draw_line(uint8_t x_start, uint8_t y_start, uint8_t x_end, uint8_t y_end, uint8_t *buffer)
{
    // Make sure x_start <= x_end and y_start <= y_end

    if (x_start > x_end)
    {
        oled_buffer_draw_line(x_end, x_start, y_start, y_end, buffer);
    }
    else if (y_start > y_end)
    {
        oled_buffer_draw_line(x_start, x_end, y_end, y_start, buffer);
    }

    // Iterates both ways, to smooth the line against sudden jumps

    if (x_start != x_end) // To avoid dividing by zero
    {
        float y_coefficient = ((float)(y_end - y_start)) / (x_end - x_start);
        for (uint8_t x = x_start; x <= x_end; ++x)
        {
            oled_buffer_set_pixel(x, (uint8_t)(y_coefficient * x + y_start), true, buffer);
        }
    }
    if (y_start != y_end) // To avoid dividing by zero
    {
        float x_coefficient = ((float)(x_end - x_start)) / (y_end - y_start);
        for (uint8_t y = y_start; y <= y_end; ++y)
        {
            oled_buffer_set_pixel((uint8_t)(x_coefficient * y + x_start), y, true, buffer);
        }
    }
}

uint8_t char_to_index(char c)
{
    // The fonts in fonts.h are the ascii characters from 32 - 126 (normally 0 - 127)
    // but skips control chars 0 - 31 and 127 (DEL)
    // Therefore, we can compute the chars as:
    return (uint8_t)c - 32;
}

void oled_buffer_print_char(char c, enum TEXT_SIZE size, uint8_t page, uint8_t column, uint8_t *buffer)
{
    uint8_t font_index = char_to_index(c);

    const unsigned char *chosen_font;

    if (size == MEDIUM)
    {
        chosen_font = (char *) font5;
    }
    else
    {
        // Large, default value
        chosen_font = (char *) font8;
    }

    for (uint8_t i = 0; i < (uint8_t)size; ++i)
    {
        // #ifndef COMPILE_FOR_TESTS
        oled_buffer_set_page_column(page, column + i, pgm_read_byte(&chosen_font[font_index * size + i]), buffer);
        // #else
        // oled_buffer_set_page_column(page, column + i, chosen_font[font_index * size + i], buffer);
    }
}

void oled_buffer_print_string(char *s, enum TEXT_SIZE size, uint8_t page, uint8_t *buffer)
{
    // Clears the page and prints the string s to the oled buffer

    // In case we don't want to start drawing right next to the left-most wall
    const uint8_t left_margin = 2;
    const uint8_t spacing = 1; // space between letters

    // Clear the current page (line)
    oled_buffer_clear_page(page, buffer);

    uint8_t length = strlen(s);

    // In case the supplied string is too long, cut it short
    if (length * (size + spacing) + left_margin > OLED_WIDTH)
    {
        length = (OLED_WIDTH - left_margin) / (size + spacing);
    }

    for (uint8_t i = 0; i < length; ++i)
    {
        oled_buffer_print_char(s[i], size, page, left_margin + i * ((uint8_t)size + spacing), buffer);
    }
}


void oled_buffer_draw_picture(const uint8_t *picture_P, uint8_t columns, uint8_t pages, uint8_t *buffer) {
    oled_buffer_clear_screen(buffer);
    for (uint8_t i = 0; i < pages; ++i) {
        for (uint8_t j = 0; j < columns; ++j) {
            int idx = i * pages + j;
            oled_buffer_set_page_column(i, j, pgm_read_byte(&picture_P[idx]), buffer);
        }
    }
}

