#include "oled.h"
#include "oled-buffer.h"

#include <util/delay.h>

volatile uint8_t* oled_cmd  = (uint8_t*)OLED_CMD_BASE;
volatile uint8_t* oled_data = (uint8_t*)OLED_DATA_BASE;

void oled_init(void)
{
    // Set display on
    *oled_cmd = 0xAF;

    // Set entire display on
    *oled_cmd = 0xA5;
}

void oled_test()
{
    // set display on
    *oled_cmd = 0xAF;

    // set entire display on
    *oled_cmd = 0xA5;

    _delay_ms(100);

    // set display off
    *oled_cmd = 0xAE;

    _delay_ms(100);
}   
/*
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
        draw_page(page, buffer);
    }
}*/