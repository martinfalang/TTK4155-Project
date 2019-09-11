#include <stdint.h>

#include "../defines.h"
#include "../oled.h"

void print_mock_buffer_to_stdout(uint8_t *arr, int width, int height) {
    char high_char = 'X';
    char low_char = ' ';

    for (int i = 0; i < OLED_WIDTH; ++i) {
        for (int j = 0; j < OLED_HEIGHT; ++j) {
            printf(get_pixel(i, j, arr) ? high_char : low_char);
        }
        printf("\n");
    }
}
