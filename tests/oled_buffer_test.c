#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "../src/defines.h"
#include "../src/oled-buffer.h"
#include "oled_buffer_utils.h"

void terminal_oled_buffer_test()
{
    // Declare mock buffer
    int oled_buffer_size = OLED_WIDTH * OLED_PAGES;
    uint8_t buffer[oled_buffer_size];

    // Initialize buffer to zero
    for (int i = 0; i < oled_buffer_size; ++i)
    {
        buffer[i] = (uint8_t)0;
    }

    // Print empty array
    printf("Printing empty mock buffer array:\n");
    print_mock_buffer_to_stdout(buffer, OLED_WIDTH, OLED_HEIGHT);

    // Set some vital pixels in the array
    printf("Setting corners high, and one pixel near the middle:\n");

    oled_set_pixel(0, 0, true, buffer);
    oled_set_pixel(0, OLED_HEIGHT - 1, true, buffer);
    oled_set_pixel(OLED_WIDTH - 1, OLED_HEIGHT - 1, true, buffer);
    oled_set_pixel(OLED_WIDTH - 1, 0, true, buffer);
    oled_set_pixel(OLED_WIDTH / 2 - 1, OLED_HEIGHT / 2 - 1, true, buffer);

    print_mock_buffer_to_stdout(buffer, OLED_WIDTH, OLED_HEIGHT);

    // Test oled_set_page_column
    printf("Setting third column in second page high:\n");

    oled_set_page_column(1, 2, 0b11111111, buffer);

    print_mock_buffer_to_stdout(buffer, OLED_WIDTH, OLED_HEIGHT);

    // Test oled_clear_screen
    printf("Clear the mock buffer:\n");

    oled_clear_screen(buffer);

    print_mock_buffer_to_stdout(buffer, OLED_WIDTH, OLED_HEIGHT);

    printf("Draw a rectangle along the edges:\n");

    oled_draw_line(0, 0, OLED_WIDTH - 1, 0, buffer); // Top line
    oled_draw_line(0, OLED_HEIGHT - 1, OLED_WIDTH - 1, OLED_HEIGHT - 1, buffer); // Bottom line
    oled_draw_line(0, 0, 0, OLED_HEIGHT - 1, buffer); // Left line
    oled_draw_line(OLED_WIDTH - 1, 0, OLED_WIDTH - 1, OLED_HEIGHT - 1, buffer); // Right line

    print_mock_buffer_to_stdout(buffer, OLED_WIDTH, OLED_HEIGHT);

    printf("Clear the screen and draw a diagonal line from top right to bottom left edge:\n");
    
    oled_clear_screen(buffer);
    oled_draw_line(0, 0, OLED_WIDTH - 1, OLED_HEIGHT - 1, buffer);
    
    print_mock_buffer_to_stdout(buffer, OLED_WIDTH, OLED_HEIGHT);

    // Test output of single char
    printf("Clear the screen and draw a medium 'K' in the top left:\n");

    oled_clear_screen(buffer);
    oled_print_char('K', MEDIUM, 0, 0, buffer);   

    print_mock_buffer_to_stdout(buffer, OLED_WIDTH, OLED_HEIGHT);

    oled_clear_screen(buffer);
    printf("Clear the screen and print a test string:\n");

    char str[] = "Funker dette?";
    oled_print_string(str, 13, MEDIUM, 0, buffer);
    
    oled_print_string("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz", 52, SMALL, 1, buffer); // Should be cut off short

    print_mock_buffer_to_stdout(buffer, OLED_WIDTH, OLED_HEIGHT);


}
