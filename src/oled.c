#include <stdint.h>

#include "defines.h"
#include "oled-buffer.h"

#define OLED_PAGE0 0b0

// Masks for page addressing mode
// See p. 27-29 in SSD1780 datasheet to verify
#define OLED_SET_PAGE_MASK 0b10110000
#define OLED_SET_COL_HI_MASK 0b00000000
#define OLED_SET_COL_LO_MASK 0b00010000

#define OLED_SET_DISPLAY_ON 0xAF
#define OLED_SET_MEM_ADDR_MODE 0x20
#define OLED_PAGE_ADDR_MODE 0x2
#define OLED_RESET_RAM_START_LINE 0b01000000

void oled_init(void)
{
    *((volatile uint16_t*)OLED_CMD_BASE) = 0xae; // display off
    *((volatile uint16_t*)OLED_CMD_BASE) = 0xa0; // Segment no remap //0xa1; //segment remap
    *((volatile uint16_t*)OLED_CMD_BASE) = 0xda; //common pads hardware: alternative
    *((volatile uint16_t*)OLED_CMD_BASE) = 0x12;
    *((volatile uint16_t*)OLED_CMD_BASE) = 0xc0; // Not alternative //0xc8; //common output scan direction:com63~com0
    *((volatile uint16_t*)OLED_CMD_BASE) = 0xa8; //multiplex ration mode:63
    *((volatile uint16_t*)OLED_CMD_BASE) = 0x3f;
    *((volatile uint16_t*)OLED_CMD_BASE) = 0xd5; //display divide ratio/osc. freq. mode
    *((volatile uint16_t*)OLED_CMD_BASE) = 0x80;
    *((volatile uint16_t*)OLED_CMD_BASE) = 0x81; //contrast control
    *((volatile uint16_t*)OLED_CMD_BASE) = 0x50;
    *((volatile uint16_t*)OLED_CMD_BASE) = 0xd9; //set pre-charge period
    *((volatile uint16_t*)OLED_CMD_BASE) = 0x21;
    *((volatile uint16_t*)OLED_CMD_BASE) = 0x20; //Set Memory Addressing Mode
    *((volatile uint16_t*)OLED_CMD_BASE) = 0x02;
    *((volatile uint16_t*)OLED_CMD_BASE) = 0xdb; //VCOM deselect level mode
    *((volatile uint16_t*)OLED_CMD_BASE) = 0x30;
    *((volatile uint16_t*)OLED_CMD_BASE) = 0xad; //master configuration
    *((volatile uint16_t*)OLED_CMD_BASE) = 0x00;
    *((volatile uint16_t*)OLED_CMD_BASE) = 0xa4; //out follows RAM content
    *((volatile uint16_t*)OLED_CMD_BASE) = 0xa6; //set normal display
    *((volatile uint16_t*)OLED_CMD_BASE) = 0xaf; // display on

    // Set to page addressing mode
    // *OLED_CMD_BASE = OLED_SET_MEM_ADDR_MODE;
    // *OLED_CMD_BASE = OLED_PAGE_ADDR_MODE; // Parameter

    // *OLED_CMD_BASE = OLED_RESET_RAM_START_LINE;

    // // Set display on (default off after reset)
    // *OLED_CMD_BASE = OLED_SET_DISPLAY_ON;
}

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
    if (0 <= col && col < OLED_WIDTH)
    {
        // Set lower nibble
        *OLED_CMD_BASE = OLED_SET_COL_LO_MASK | (0x0F & col); // Mask out lower four bits
        // Set higher nibbler
        *OLED_CMD_BASE = OLED_SET_COL_HI_MASK | (0x0F & (col >> 4)); // Mask out higher four bits
    }
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

void oled_draw_screen(uint8_t *buffer)
{
    for (int page = 0; page < OLED_PAGES; ++page)
    {
        draw_page_to_screen(page, buffer);
    }
}