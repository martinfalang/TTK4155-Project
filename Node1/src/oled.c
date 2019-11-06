#include <stdint.h>

#include "../../lib/inc/defines.h"
#include "oled-buffer.h"

#define OLED_PAGE0 0b0

// Masks for page addressing mode
// See p. 27-29 in SSD1780 datasheet to verify
#define OLED_SET_PAGE_MASK 0b10110000
#define OLED_SET_COL_HI_MASK 0x10
#define OLED_SET_COL_LO_MASK 0x00

volatile char *const oled_cmd_ptr = (char *)0x1000;
volatile char *const oled_data_ptr = (char *)0x1200;


/**
 * @brief Writes a command to the OLED controller
 * 
 * @param cmd Command to send
 */
void oled_write_c(uint8_t cmd)
{
    *oled_cmd_ptr = cmd;
}

/**
 * @brief Sends data to the OLED controller to print at the location of the cursor
 * 
 * @param data 
 */
void oled_write_d(uint8_t data)
{
    *oled_data_ptr = data;
}

void oled_init(void)
{

    oled_write_c(0xae); // display off
    oled_write_c(0xa1); //segment remap
    oled_write_c(0xda); //common pads hardware: alternative
    oled_write_c(0x12);
    oled_write_c(0xc8); //common output scan direction:com63~com0
    oled_write_c(0xa8); //multiplex ration mode:63
    oled_write_c(0x3f);
    oled_write_c(0xd5); //display divide ratio/osc. freq. mode
    oled_write_c(0x80);
    oled_write_c(0x81); //contrast control
    oled_write_c(0x50);
    oled_write_c(0xd9); //set pre-charge period
    oled_write_c(0x21);
    oled_write_c(0x20); //Set Memory Addressing Mode
    oled_write_c(0x02);
    oled_write_c(0xdb); //VCOM deselect level mode
    oled_write_c(0x30);
    oled_write_c(0xad); //master configuration
    oled_write_c(0x00);
    oled_write_c(0xa4); //out follows RAM content
    oled_write_c(0xa6); //set normal display
    oled_write_c(0xaf); // display on
}

void oled_set_page(uint8_t page)
{
    // Page must be in range [0, 7]
    if (0 <= page && page < OLED_PAGES)
    {
        oled_write_c(OLED_SET_PAGE_MASK | page);
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
        oled_write_c(OLED_SET_COL_LO_MASK | (0x0F & col)); // Mask out lower four bits
        // Set higher nibbler
        oled_write_c(OLED_SET_COL_HI_MASK | (0x0F & (col >> 4))); // Mask out higher four bits
    }
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
        oled_write_d(buffer[page_start_index + col]);
    }
}

void oled_draw_screen(uint8_t *buffer)
{
    for (int page = 0; page < OLED_PAGES; ++page)
    {
        draw_page_to_screen(page, buffer);
    }
}