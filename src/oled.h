#ifndef OLED_H
#define OLED_H

#include <stdbool.h>
#include <stdint.h>

int get_index(int x, int y);

void set_pixel(int x, int y, bool val, uint8_t *arr);

bool get_pixel(int x, int y, uint8_t *arr);

// void write_to_screen();



#endif /* OLED_H */