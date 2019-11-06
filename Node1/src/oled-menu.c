#include "../../lib/inc/defines.h"

#include <avr/io.h> // For led toggle

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "oled-menu.h"
#include "joystick.h"
#include "oled-buffer.h"
#include "oled.h"

#define NUM_MAIN_MENU_ELEMENTS 3
#define NUM_SONG_MENU_ELEMENTS 2

// Global variables
// Allows to change menus by calling functions
static oled_menu_t *p_current_menu;
static oled_menu_t main_menu;
static oled_menu_t song_menu;
static oled_menu_el_t main_menu_elements[NUM_MAIN_MENU_ELEMENTS];
static oled_menu_el_t song_menu_elements[NUM_SONG_MENU_ELEMENTS];

static joy_btn_dir_t prev_dir; // Previous direction
static bool menu_needs_update;

bool oled_menu_should_update()
{
    // Because menu_needs_update is not available from other files, i.e. main.c
    return menu_needs_update;
}

void toggle_led(void)
{
    PORTE ^= 1 << PE0;
}

void draw_oled_menu(oled_menu_t *menu, uint8_t *buffer)
{
    // Clear the buffer
    oled_buffer_clear_screen(buffer);

    // Draw the header
    oled_buffer_print_string(menu->header_string, LARGE, 0, buffer);

    // Draw the elements
    char row_string[32] = ""; // TODO: Find optimal size
    // strcpy((char *)row_string, "");

    const char *selected_marker = "> ";
    const char *not_selected_marker = "  ";

    for (uint8_t i = 0; i < menu->num_elements; ++i)
    {
        strcpy(row_string, "");

        bool is_selected = menu->selected_idx == i;
        if (is_selected)
        {
            // Add "> " before the string
            strcat(row_string, selected_marker);
        }
        else
        {
            // Add "  " before the string
            strcat(row_string, not_selected_marker);
        }

        strcat(row_string, menu->elements[i].element_text);

        // Print the string to the buffer
        oled_buffer_print_string(row_string, MEDIUM, i + 1, buffer);
    }
}

oled_menu_action_t oled_menu_get_empty_action(void)
{
    // Returns an empty action
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

oled_menu_el_t oled_menu_create_element(char *text, oled_menu_action_t action)
{
    oled_menu_el_t element;

    strcpy(element.element_text, text);
    element.select_action = action;

    return element;
}

void oled_menu_init_menus(void)
{
    // Allocates memory and gives a pointer to a main menu
    main_menu.num_elements = 3;
    // main_menu.header_string = "Main Menu";
    strcpy(main_menu.header_string, "Main Menu");
    main_menu.selected_idx = 0;
    main_menu.back_action = oled_menu_get_empty_action();

    main_menu_elements[0] = oled_menu_create_element("Toggle LED", oled_menu_create_func_ptr_action(&toggle_led));
    main_menu_elements[1] = oled_menu_create_element("Toggle LED!!!", oled_menu_create_func_ptr_action(&toggle_led));
    main_menu_elements[2] = oled_menu_create_element("Songs", oled_menu_create_menu_ptr_action(&song_menu));
    main_menu.elements = main_menu_elements;

    // song_menu.header_string = "Songs";
    strcpy(song_menu.header_string, "Songs");
    song_menu.num_elements = 2;
    song_menu.back_action = oled_menu_create_menu_ptr_action(&main_menu);
    song_menu.selected_idx = 0;

    song_menu_elements[0] = oled_menu_create_element("Song 1 goes here", oled_menu_create_func_ptr_action(&toggle_led));
    song_menu_elements[1] = oled_menu_create_element("Song 2 goes here", oled_menu_get_empty_action());
    song_menu.elements = song_menu_elements;
}

void oled_menu_init(uint8_t *buffer)
{
    // Create the dynamically allocated main menu
    oled_menu_init_menus();
    p_current_menu = &main_menu;

    prev_dir = NEUTRAL; // Previous direction
    menu_needs_update = false;

    draw_oled_menu(p_current_menu, buffer);
    oled_draw_screen(buffer);
}

void oled_menu_check_if_needs_update(void)
{
    // Check if the joystick direction has changed since last change
    joy_btn_dir_t dir = joystick_get_direction();

    if (dir != prev_dir)
    {
        menu_needs_update = true;
        prev_dir = dir;
    }
}

void oled_menu_update(uint8_t *buffer)
{
    // Updates the menu based on the input of prev_dir.
    // Should be called when menu_needs_update is true
    switch (prev_dir)
    {
    case RIGHT:
        oled_menu_perform_action(
            p_current_menu->elements[p_current_menu->selected_idx].select_action);
        break;
    case LEFT:
        oled_menu_perform_action(p_current_menu->back_action);
        break;
    case UP:
        if (p_current_menu->selected_idx > 0)
        {
            --p_current_menu->selected_idx;
        }
        else
        {
            p_current_menu->selected_idx = p_current_menu->num_elements - 1;
        }
        break;
    case DOWN:
        if (p_current_menu->selected_idx < p_current_menu->num_elements - 1)
        {
            ++p_current_menu->selected_idx;
        }
        else
        {
            p_current_menu->selected_idx = 0;
        }
        break;
    }

    menu_needs_update = false;

    draw_oled_menu(p_current_menu, buffer);
    oled_draw_screen(buffer);
}