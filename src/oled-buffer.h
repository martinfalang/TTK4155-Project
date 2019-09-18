#ifndef OLED_H
#define OLED_H

#include <stdbool.h>
#include <stdint.h>

/*
    General OLED-buffer (given 8-bit column height)
*/

// Low level functions
void oled_set_pixel(uint8_t x, uint8_t y, bool val, uint8_t *buffer);

bool oled_get_pixel(uint8_t x, uint8_t y, uint8_t *buffer);

void oled_set_page_column(int page, int column, uint8_t data, uint8_t *buffer);

// System functions
void oled_clear_page(uint8_t page, uint8_t *buffer);

void oled_clear_screen(uint8_t *buffer);
// void write_to_screen();

// Text functions
enum TEXT_SIZE
{
    SMALL = 4,
    MEDIUM = 5,
    LARGE = 8
};

void oled_print_char(char c, enum TEXT_SIZE size, uint8_t page, uint8_t column, uint8_t *buffer);

void oled_print_string(char *s, uint8_t length, enum TEXT_SIZE size, uint8_t page, uint8_t *buffer);

// Drawing functions
void oled_draw_line(uint8_t x_start, uint8_t y_start, uint8_t x_end, uint8_t y_end, uint8_t *buffer);

#endif /* OLED_H */