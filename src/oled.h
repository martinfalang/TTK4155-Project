#ifndef OLED_H
#define OLED_H

#include <stdbool.h>
#include <stdint.h>

// int get_index(int x, int y);

void oled_set_pixel(uint8_t x, uint8_t y, bool val, uint8_t *arr);

bool oled_get_pixel(uint8_t x, uint8_t y, uint8_t *arr);

void oled_set_page_column(int page, int column, uint8_t data, uint8_t *arr);

void oled_clear_screen(uint8_t *arr);

void oled_draw_line(uint8_t x_start, uint8_t y_start, uint8_t x_end, uint8_t y_end, uint8_t *arr);
// void write_to_screen();

#endif /* OLED_H */