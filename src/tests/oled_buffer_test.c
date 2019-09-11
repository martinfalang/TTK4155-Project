#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "../defines.h"
#include "../oled.h"
#include "oled_buffer_utils.h"


void terminal_oled_buffer_test() {
    // Declare mock buffer
    int oled_buffer_size = OLED_WIDTH * OLED_PAGES;
    uint8_t buffer[oled_buffer_size];

    // Initialize buffer to zero
    for (int i = 0; i < oled_buffer_size; ++i) {
        buffer[i] = (uint8_t) 0;
    }

    // Print empty array
    printf("Printing empty mock buffer array:\n");
    print_mock_buffer_to_stdout(buffer, OLED_WIDTH, OLED_HEIGHT);

    // Set some vital pixels in the array
    printf("Setting corners high, and one pixel near the middle:\n");
    
    set_pixel(0, 0, true, buffer);
    set_pixel(0, OLED_HEIGHT - 1, true, buffer);
    set_pixel(OLED_WIDTH - 1, OLED_HEIGHT - 1, true, buffer);
    set_pixel(OLED_WIDTH - 1, 0, true, buffer);

    print_mock_buffer_to_stdout(buffer, OLED_WIDTH, OLED_HEIGHT);
    

}
