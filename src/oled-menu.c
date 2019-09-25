#include <avr/io.h> // For led toggle
#include <stdbool.h>
#include <stdio.h>
#include <util/delay.h>

#include "oled-menu.h"
#include "defines.h"
#include "joystick.h"
#include "oled-buffer.h"
#include "oled.h"

void oled_menu_navigate_up();
void oled_menu_navigate_down();
void oled_menu_navigate_left();
void oled_menu_navigate_right();

void oled_menu_select(oled_menu_el_t element)
{
    (*element.on_select)();
}
void oled_menu_back(oled_menu_el_t element);

void toggle_led(void)
{
    PORTB ^= 1 << PB0;
}

void draw_oled_menu(oled_menu_t *menu, uint8_t *buffer)
{
    // Clear the buffer
    oled_buffer_clear_screen(buffer);

    // Draw the header
    oled_buffer_print_string(
        menu->header_string,
        menu->header_length, LARGE, 0, buffer);

    // Draw the elements
    char * row_string[32]; // TODO: Find optimal size
    row_string[0] = '\0'; // Initialize row_string so it's empty
    
    char * selected_marker = "> ";
    char * not_selected_marker = "  ";

    for (uint8_t i = 0; i < menu->num_elements; ++i)
    {
        bool is_selected = menu->selected_idx == i;
        if (is_selected)
        {
            // Add "> " before the string
            strcat(row_string, selected_marker);
        } else {
            // Add "  " before the string
            strcat(row_string, not_selected_marker);            
        }

        strcat(row_string, menu->elements[i].element_text);

        // Print the string to the buffer
        oled_buffer_print_string(row_string, 2 + menu->elements[i].text_length, MEDIUM, i + 1, buffer);
    }
}

void oled_menu_init(uint8_t * buffer)
{
    // Make main menu elements
    oled_menu_el_t test_element;

    test_element.element_text = "Example element";
    test_element.text_length = 9;
    test_element.on_select = &toggle_led;
    test_element.on_back = &toggle_led;

    oled_menu_t mm; // main menu

    char *header = "Header";
    mm.elements = &test_element;
    mm.num_elements = 1;
    mm.header_string = header;
    mm.header_length = 6;
    mm.selected_idx = 0;

    bool btn_is_pressed = false;
    while (1)
    {
        if (joystick_read_btn)
        {
            if (!btn_is_pressed)
            {
                // Button was not pressed before, but was during this iteration
                btn_is_pressed = true;
                oled_menu_select(mm.elements[mm.selected_idx]);
            }
        }
        else
        {
            btn_is_pressed = false;
        }

        draw_oled_menu(&mm, buffer);
        oled_draw_screen(buffer);
        
        _delay_ms(16); // Should give about 60 fps
    }
}