#include "oled.h"
#include "defines.h"

#include <stdbool.h>
#include <stdint.h>

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

int get_index(int x, int y)
{
    return (y / OLED_PAGES) * OLED_WIDTH + x; // Calculate index corresponding to x, y in buffer array "arr"
}

void set_pixel(int x, int y, bool val, uint8_t *arr)
{
    int index = get_index(x, y);

    if (val)
    {
        arr[index] |= (1 << (y % 8)); // Set the bit at the given position
    }
    else
    {
        arr[index] &= !(1 << (y % 8)); // Clear the bit at the given position
    }
}

bool get_pixel(int x, int y, uint8_t *arr) {
    return (bool) ((1 << (y % 8)) & arr[get_index(x, y)]);
}

void write_to_screen();