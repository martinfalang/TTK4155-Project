#include <avr/io.h> // For led toggle
#include <util/delay.h>

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

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
    oled_buffer_print_string(menu->header_string, LARGE, 0, buffer);

    // Draw the elements
    char *row_string[32]; // TODO: Find optimal size
    row_string[0] = '\0'; // Initialize row_string so it's empty

    char *selected_marker = "> ";
    char *not_selected_marker = "  ";

    for (uint8_t i = 0; i < menu->num_elements; ++i)
    {
        bool is_selected = menu->selected_idx == i;
        if (is_selected)
        {
            // Add "> " before the string
            strcat((char *) row_string, selected_marker);
        }
        else
        {
            // Add "  " before the string
            strcat((char *) row_string, not_selected_marker);
        }

        strcat((char *) row_string, menu->elements[i].element_text);

        // Print the string to the buffer
        oled_buffer_print_string((char *) row_string, MEDIUM, i + 1, buffer);
    }
}

// Pointers to menu elements
// Allows to change menus by calling functions
static oled_menu_el_t *p_main_menu;
static oled_menu_el_t *p_sub_menu;
static oled_menu_el_t *p_current_menu;

void go_to_main_menu(void) {
    p_current_menu = p_main_menu;
}

void go_to_submenu(void) {
    p_current_menu = p_sub_menu;
}

void oled_menu_init(uint8_t *buffer)
{
    // Make main menu elements
    oled_menu_el_t test_element;

    test_element.element_text = "Example element";
    test_element.on_select = &toggle_led;
    test_element.prev_menu = NULL;

    oled_menu_t mm; // main menu

    char *header = "Header";
    mm.elements = &test_element;
    mm.num_elements = 1;
    mm.header_string = header;
    mm.selected_idx = 0;

    // Make sub menu elements
    oled_menu_el_t sub_el_1;

    sub_el_1.element_text = "Submenu element 1";
    sub_el_1.on_select = &toggle_led;
    sub_el_1.prev_menu = &mm;

    oled_menu_el_t sub_el_2;

    sub_el_2.element_text = "Submenu element 2";
    sub_el_2.on_select = &toggle_led;
    sub_el_2.prev_menu = &mm;

    // Make sub-menu elements
    oled_menu_t sub;

    oled_menu_el_t sub_menu_elements[2];
    sub_menu_elements[0] = sub_el_1;
    sub_menu_elements[1] = sub_el_2;

    sub.elements = sub_menu_elements;

    // sub.header_string = 


    joy_btn_dir_t prev_dir = NEUTRAL; // Previous direction

    while (1)
    {
        joy_btn_dir_t dir = joystick_get_direction();

        if (dir != prev_dir)
        {
            switch (dir)
            {
            case RIGHT:
                current_menu->elements[current_menu->selected_idx].on_select();
                break;
            case LEFT:
                if (current_menu->elements[current_menu->selected_idx].prev_menu != NULL)
                {
                    current_menu = current_menu->elements[current_menu->selected_idx].prev_menu;
                }
                break;
            case UP:
                if (current_menu->selected_idx >= 0)
                {
                    --current_menu->selected_idx;
                }
                break;
            case DOWN:
                if (current_menu->selected_idx < current_menu->num_elements)
                {
                    ++current_menu->selected_idx;
                }
            }

            prev_dir = dir;

            _delay_ms(16); // Should give about 60 fps
        }

        draw_oled_menu(current_menu, buffer);
        oled_draw_screen(buffer);
    }
}