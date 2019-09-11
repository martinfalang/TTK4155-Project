#include "oled.h"
#include "defines.h"

#include <stdbool.h>
#include <stdint.h>

#include <stdio.h> // TODO: REMOVE

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

uint16_t oled_get_index(uint8_t x, uint8_t y)
{
    return (y / OLED_PAGES) * OLED_WIDTH + x; // Calculate index corresponding to x, y in buffer array "arr"
}

void oled_set_pixel(uint8_t x, uint8_t y, bool val, uint8_t *arr)
{
    int index = oled_get_index(x, y);

    if (val)
    {
        arr[index] |= (1 << (y % 8)); // Set the bit at the given position
    }
    else
    {
        arr[index] &= !(1 << (y % 8)); // Clear the bit at the given position
    }
}

void oled_set_page_column(int page, int column, uint8_t data, uint8_t *arr)
{
    arr[page * OLED_WIDTH + column] = data;
}

bool oled_get_pixel(uint8_t x, uint8_t y, uint8_t *arr)
{
    return (bool)((1 << (y % 8)) & arr[oled_get_index(x, y)]);
}

void oled_clear_screen(uint8_t *arr)
{
    for (uint8_t p = 0; p < OLED_PAGES; ++p)
    {
        for (uint8_t col = 0; col < OLED_WIDTH; ++col)
        {
            oled_set_page_column(p, col, 0, arr);
        }
    }
}

void oled_draw_line(uint8_t x_start, uint8_t y_start, uint8_t x_end, uint8_t y_end, uint8_t *arr)
{
    // Make sure x_start <= x_end and y_start <= y_end
    printf("(%d, %d),  (%d, %d)\n", x_start, y_start, x_end, y_end);
    
    if (x_start > x_end)
    {
        oled_draw_line(x_end, x_start, y_start, y_end, arr);
    }
    else if (y_start > y_end)
    {
        oled_draw_line(x_start, x_end, y_end, y_start, arr);
    }

    // Iterates both ways, to smooth the line against sudden jumps

    if (x_start != x_end) // To avoid dividing by zero
    {
        printf("x-iteration\n");
        uint8_t y_coefficient = (y_end - y_start) / (x_end - x_start);
        for (uint8_t x = x_start; x <= x_end; ++x)
        {
            printf("(%d, %d)\n", x, (uint8_t) y_coefficient * x + y_start);
            oled_set_pixel(x, (uint8_t) y_coefficient * x + y_start, true, arr);
        }
    }

    if (y_start != y_end) 
    {
        printf("y-iteration\n");
        uint8_t x_coefficient = (x_end - x_start) / (y_end - y_start);
        for (uint8_t y = y_start; y <= y_end; ++y)
        {
            oled_set_pixel((uint8_t) x_coefficient * y + x_start, y, true, arr);
        }
    }
}

void write_to_screen();