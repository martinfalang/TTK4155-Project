#include <stdint.h>

#include "defines.h"
#include "oled-buffer.h"

#define OLED_PAGE0 0b0

// Masks for page addressing mode
// See p. 27-29 in SSD1780 datasheet to verify
#define OLED_SET_PAGE_MASK   0b10110000
#define OLED_SET_COL_HI_MASK 0b00000000
#define OLED_SET_COL_LO_MASK 0b00010000

#define OLED_SET_DISPLAY_ON 0xAF


void oled_set_page(uint8_t page)
{
    // Page must be in range [0, 7]
    if (0 <= page && page < OLED_PAGES)
    {
        *OLED_CMD_BASE = OLED_SET_PAGE_MASK | page;
    }
}

void oled_set_col(uint8_t col)
{
    // Col must be in range [0, 127]

    // Note that in page addressing mode, the column auto-increments after write, s.t.
    // calling this function is only required when starting to write to the beginning of a page
    if (0 <= col && col < OLED_WIDTH) {
        // Set lower nibble
        *OLED_CMD_BASE = OLED_SET_COL_LO_MASK | (0x0F & col); // Mask out lower four bits
        // Set higher nibbler
        *OLED_CMD_BASE = OLED_SET_COL_HI_MASK | (0x0F & (col >> 4)); // Mask out higher four bits
    }
}

void oled_init(void)
{
    // Set display on (default off after reset)
    *OLED_CMD_BASE = OLED_SET_DISPLAY_ON;

    oled_buffer_clear(OLED_BUFFER_BASE);
}

void oled_test_screen(void)
{
}




void draw_page_to_screen(uint8_t page, uint8_t *buffer)
{
    // Send commands to start on the beginning of the page we want
    // to write to
    oled_set_page(page);
    oled_set_col(0);

    uint16_t page_start_index = page * OLED_WIDTH;
    
    for (int col = 0; col < OLED_WIDTH; ++col)
    {
        // Write from buffer to screen
        *OLED_DATA_BASE = buffer[page_start_index + col];
    }
}

void draw_screen(uint8_t *buffer)
{
    for (int page = 0; page < OLED_PAGES; ++page)
    {
        draw_page_to_screen(page, buffer);
    }
}