#include <stdint.h>

#include "defines.h"
#include "oled-buffer.h"



void oled_init(void)
{
    // Set display on
}

void oled_test_screen(void)
{
    
}

void draw_page_to_screen(uint8_t page, uint8_t *buffer)
{
    for (int col = 0; col < OLED_WIDTH; ++col) {
        // Write to 
    }
}

void draw_screen(uint8_t *buffer)
{
    for (int page = 0; page < OLED_PAGES; ++page)
    {
        draw_page(page, buffer)
    }
}