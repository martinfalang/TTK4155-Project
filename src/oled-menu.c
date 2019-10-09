#include "defines.h"

#include <avr/io.h> // For led toggle
#include <util/delay.h>

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "oled-menu.h"
#include "joystick.h"
#include "oled-buffer.h"
#include "oled.h"

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
    strcpy((char *)row_string, "");

    const char *selected_marker = "> ";
    const char *not_selected_marker = "  ";

    for (uint8_t i = 0; i < menu->num_elements; ++i)
    {
        strcpy((char *) row_string, "");
        
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

oled_menu_el_t oled_menu_create_element(char * text, oled_menu_action_t action) {
    oled_menu_el_t element;

    element.element_text = text;
    element.select_action = action;
    
    return element;
}

oled_menu_t * oled_menu_get_main(void) {
    // Allocates memory and gives a pointer to a main menu
    oled_menu_t * mm = malloc(sizeof(oled_menu_t));  // Main menu
    oled_menu_t * song_menu = malloc(sizeof(oled_menu_t)); // Menu showing available songs for buzzer

    mm->num_elements = 3;
    mm->header_string = "Main Menu";
    mm->selected_idx = 0;
    mm->back_action = oled_menu_get_empty_action();

    // Make sub menu elements
    // oled_menu_el_t * main_el_1 = malloc(sizeof(oled_menu_el_t));

    // main_el_1->element_text = "Toggle LED";
    // main_el_1->select_action = oled_menu_create_func_ptr_action(&toggle_led);

    // oled_menu_el_t * main_el_2 = malloc(sizeof(oled_menu_el_t));

    // main_el_2->element_text = "Toggle LED, but another element";
    // main_el_2->select_action = oled_menu_create_func_ptr_action(&toggle_led);

    // oled_menu_el_t * main_el_3 = malloc(sizeof(oled_menu_el_t));

    // main_el_3->element_text = "Songs";
    // main_el_3->select_action = oled_menu_create_menu_ptr_action(&song_menu);

    oled_menu_el_t * main_menu_elements = malloc(mm->num_elements * sizeof(oled_menu_el_t));
    main_menu_elements[0] = oled_menu_create_element("Toggle LED", oled_menu_create_func_ptr_action(&toggle_led));
    main_menu_elements[1] = oled_menu_create_element("Toggle LED, but another element", oled_menu_create_func_ptr_action(&toggle_led));
    main_menu_elements[2] = oled_menu_create_element("Songs", oled_menu_create_menu_ptr_action(&song_menu));
    mm->elements = main_menu_elements;

    // Make sub-menu elements
    // oled_menu_el_t * song_el_1 = malloc(sizeof(oled_menu_el_t));
    // oled_menu_el_t * song_el_2 = malloc(sizeof(oled_menu_el_t));

    // song_el_1->element_text = "Song 1 goes here";
    // song_el_1->select_action = oled_menu_create_func_ptr_action(&toggle_led);

    // song_el_2->element_text = "Song 2 goes here";
    // song_el_2->select_action = oled_menu_get_empty_action();

    song_menu->header_string = "Songs";
    song_menu->num_elements = 2;
    song_menu->back_action = oled_menu_create_menu_ptr_action(&mm);
    song_menu->selected_idx = 0;

    oled_menu_el_t * song_menu_elements = malloc(song_menu->num_elements * sizeof(oled_menu_el_t));

    song_menu_elements[0] = oled_menu_create_element("Song 1 goes here", oled_menu_create_func_ptr_action(&toggle_led));
    song_menu_elements[1] = oled_menu_create_element("Song 2 goes here", oled_menu_get_empty_action());

    song_menu->elements = song_menu_elements;

    return mm;
}

// Pointers to menus
// Allows to change menus by calling functions
static oled_menu_t *p_current_menu;
static oled_menu_t *p_main_menu;


void oled_menu_init(uint8_t *buffer)
{
    p_main_menu = oled_menu_get_main();
    p_current_menu = p_main_menu;

    joy_btn_dir_t prev_dir = NEUTRAL; // Previous direction

    draw_oled_menu(p_current_menu, buffer);
    oled_draw_screen(buffer);

    while (1)
    {
        joy_btn_dir_t dir = joystick_get_direction();

        if (dir != prev_dir)
        {
            switch (dir)
            {
            case RIGHT:
                oled_menu_perform_action(
                    p_current_menu->elements[p_current_menu->selected_idx].select_action
                );
                break;
            case LEFT:
                oled_menu_perform_action(p_current_menu->back_action);
                break;
            case UP:
                if (p_current_menu->selected_idx > 0)
                {
                    --p_current_menu->selected_idx;
                } else {
                    p_current_menu->selected_idx = p_current_menu->num_elements - 1;
                }
                break;
            case DOWN:
                if (p_current_menu->selected_idx < p_current_menu->num_elements - 1)
                {
                    ++p_current_menu->selected_idx;
                } else {
                    p_current_menu->selected_idx = 0;
                }
                break;
            }

            prev_dir = dir;

            draw_oled_menu(p_current_menu, buffer);
            oled_draw_screen(buffer);
        }
        _delay_ms(16); // Should give about 60 fps
    }
}