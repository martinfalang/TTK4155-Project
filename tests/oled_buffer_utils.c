#include <stdint.h>
#include <stdio.h>

#include "../src/defines.h"
#include "../src/oled-buffer.h"

void print_mock_buffer_to_stdout(uint8_t *arr, int width, int height)
{
    char high_char = 'X';
    char low_char = '.';

    for (int y = 0; y < OLED_HEIGHT; ++y)
    {
        for (int x = 0; x < OLED_WIDTH; ++x)
        {
            printf("%c", oled_get_pixel(x, y, arr) ? high_char : low_char);
        }
        printf("\n");
    }
}
