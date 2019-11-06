#include "../../lib/inc/defines.h"

#include <avr/interrupt.h>
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

void _timer_init(void);

bool oled_menu_should_update()
{
    // Because menu_needs_update is not available from other files, i.e. main.c
    if (menu_needs_update) {
        joy_btn_dir_t dir = joystick_get_direction();

        if (prev_dir != dir) {
            prev_dir = dir;
            return true;
        }
    }
    return false;
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
    
    // The timer prevented can from working. Stopped 
    // the entire program
    // _timer_init();
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
    prev_dir = joystick_get_direction();
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

/* void _timer_init(void) {
    // Initializes a timer that raises an interrupt 
    // setting a flag telling if the screen should be updated

    // Set Force Output Compare high
    TCCR2 |= (1 << FOC2);

    // Set Clear-to-Clear mode for clock 2
    TCCR2 |= (1 << WGM21);
    TCCR2 &= ~(1 << WGM20);

    // Set the register to clear on match
    TCCR2 |= (1 << COM21);
    TCCR2 &= ~(1 << COM20);

    // Set clock prescaler to CLT_T2_S/1024
    TCCR2 |= (1 << CS20) | (1 << CS21) | (1 << CS22);

    // Set the timer counter register to 0
    TCNT2 = 0; 

    // Set output compare register to 80, which should amount to 
    // interrupts about 60 times per second
    OCR2 = 80;

    // Activate Timer2 Output Compare in interrupt mask
    TIMSK |= (1 << OCIE2);

    // Enable interrupts globally
    SREG |= (1 << SREG_I);
} */
/* 
ISR(TIMER2_COMP_vect) {
    // Interrupt service routine for checking joystick if new input has occured
    // s.t. the screen should be updated
    menu_needs_update = true;
} */