#include "../../lib/inc/defines.h"

#include <avr/io.h> // For led toggle
#include <util/delay.h>

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "oled-menu.h"
#include "joystick.h"
#include "oled-buffer.h"
#include "oled.h"
#include "oled_timer.h"

void oled_menu_navigate_up();
void oled_menu_navigate_down();
void oled_menu_navigate_left();
void oled_menu_navigate_right();

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
            strcat((char *)row_string, selected_marker);
        }
        else
        {
            // Add "  " before the string
            strcat((char *)row_string, not_selected_marker);
        }

        strcat((char *)row_string, menu->elements[i].element_text);

        // Print the string to the buffer
        oled_buffer_print_string((char *)row_string, MEDIUM, i + 1, buffer);
    }
}

// Pointers to menus
// Allows to change menus by calling functions
static oled_menu_t *p_current_menu;
static bool g_oled_should_update = true;
static joy_btn_dir_t prev_dir = NEUTRAL;

oled_menu_action_t oled_menu_get_empty_action(void)
{
    // Returns an empty action, e.g. for use with menu elements that do not have
    oled_menu_action_t action;
    action.ptr.p_menu = NULL;
    action.is_func_ptr = false;

    return action;
}

oled_menu_action_t oled_menu_create_menu_ptr_action(oled_menu_t *p_menu)
{
    oled_menu_action_t action;

    action.is_func_ptr = false;
    action.ptr.p_menu = p_menu;

    return action;
}

oled_menu_action_t oled_menu_create_func_ptr_action(void *p_func)
{
    oled_menu_action_t action;

    action.is_func_ptr = true;
    action.ptr.p_menu = p_func;

    return action;
}

void oled_menu_perform_action(oled_menu_action_t action)
{
    if (action.is_func_ptr && action.ptr.p_func != NULL)
    {
        // Call function in function pointer
        action.ptr.p_func();
    }
    else if (action.ptr.p_menu != NULL)
    {
        // Change current menu to the pointer in the performed action if it is not NULL
        p_current_menu = action.ptr.p_menu;
    }
}

// oled_menu_el_t get_play_ping_pong_element() {
//     oled_menu_el_t element;
//     element.element_text = "Play Ping Pong (placeholder)";
//     element.select_action = oled_menu_get_empty_action();
// }

// oled_menu_el_t get_songs_element() {
//     oled_menu_el_t element;
//     element.element_text = "Songs";
//     element.select_action = get_empty_menu_action();
// }

void oled_menu_init(uint8_t *buffer)
{
    // Make main menu elements
    oled_menu_el_t test_element;

    test_element.element_text = "Example element";
    test_element.select_action.ptr.p_func = &toggle_led;
    test_element.select_action.is_func_ptr = true;

    // test_element.prev_menu = NULL;

    oled_menu_t mm;        // Main menu
    oled_menu_t song_menu; // Menu showing available songs for buzzer

    char *header = "Header";
    mm.elements = &test_element;
    mm.num_elements = 3;
    mm.header_string = header;
    mm.selected_idx = 0;
    mm.back_action = oled_menu_get_empty_action();

    // Make sub menu elements
    oled_menu_el_t main_el_1;

    main_el_1.element_text = "Toggle LED";
    main_el_1.select_action.ptr.p_func = &toggle_led;
    main_el_1.select_action.is_func_ptr = true;

    oled_menu_el_t main_el_2;

    main_el_2.element_text = "Toggle LED, but another element";
    main_el_2.select_action.ptr.p_func = &toggle_led;
    main_el_2.select_action.is_func_ptr = true;

    oled_menu_el_t main_el_3;

    main_el_3.element_text = "Songs";
    main_el_3.select_action = oled_menu_create_menu_ptr_action(&song_menu);

    oled_menu_el_t main_menu_elements[3] = {main_el_1, main_el_2, main_el_3};
    mm.elements = main_menu_elements;

    // Make sub-menu elements
    oled_menu_el_t song_el_1;

    song_el_1.element_text = "Song 1 goes here";
    song_el_1.select_action.ptr.p_func = &toggle_led;
    song_el_1.select_action.is_func_ptr = true;

    oled_menu_el_t song_el_2;

    song_el_2.element_text = "Song 2 goes here";
    song_el_2.select_action = oled_menu_get_empty_action();
    song_el_2.select_action.is_func_ptr = true;

    oled_menu_el_t song_menu_elements[2] = {song_el_1, song_el_2};

    song_menu.elements = song_menu_elements;
    song_menu.num_elements = 2;
    song_menu.back_action = oled_menu_create_menu_ptr_action(&mm);

    prev_dir = NEUTRAL; // Previous direction

    // Draw the screen once
    draw_oled_menu(p_current_menu, buffer);
    oled_draw_screen(buffer);

    // Start the interrupt-driven timer, which updates the screen regularly
    oled_timer_init();

}

void oled_menu_check_if_needs_update(void)
{
    joy_btn_dir_t dir = joystick_get_direction();

    if (dir != prev_dir)
    {
        g_oled_should_update = true;

        switch (dir)
        {
        case RIGHT:
            oled_menu_perform_action(
                p_current_menu->elements[p_current_menu->selected_idx].select_action);
            break;
        case LEFT:
            oled_menu_perform_action(p_current_menu->back_action);
            break;
        case UP:
            if (p_current_menu->selected_idx >= 0)
            {
                --p_current_menu->selected_idx;
            }
            break;
        case DOWN:
            if (p_current_menu->selected_idx < p_current_menu->num_elements)
            {
                ++p_current_menu->selected_idx;
            }
            break;
        }

        prev_dir = dir;
    }
}

void oled_menu_update_if_needed(void) {
    if (g_oled_should_update) {
        g_oled_should_update = false;

        draw_oled_menu(p_current_menu, OLED_BUFFER_BASE);
        oled_draw_screen(OLED_BUFFER_BASE);
    }
}