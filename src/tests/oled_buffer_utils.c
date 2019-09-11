#include <stdint.h>
#include <stdio.h>

#include "../defines.h"
#include "../oled.h"

void print_mock_buffer_to_stdout(uint8_t *arr, int width, int height)
{
    char high_char = 'X';
    char low_char = '.';

    for (int j = 0; j < OLED_HEIGHT; ++j)
    {
        for (int i = 0; i < OLED_WIDTH; ++i)
        {
            printf("%c", oled_get_pixel(i, j, arr) ? high_char : low_char);
        }
        printf("\n");
    }
}
