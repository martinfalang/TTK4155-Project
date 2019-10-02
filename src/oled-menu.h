/*
    Menu framework for use with OLED screen
*/

#ifndef OLED_MENU_H
#define OLED_MENU_H

#include <stdint.h>
#include <stdbool.h>

// Forward declaration to allow pointer from both element to menu
// and menu to element
typedef struct oled_menu oled_menu_t; 

typedef union menu_action_ptr {
    oled_menu_t * p_menu;
    void (* p_func)(void);
} oled_menu_action_ptr_t;

typedef struct menu_el_action {
    oled_menu_action_ptr_t ptr;
    bool is_func_ptr; // True if ptr is a function pointer, false if it is a oled_menu_t pointer
} oled_menu_action_t;

typedef struct oled_menu_el {
    char *element_text;
    oled_menu_action_t select_action; // When pushing joystick to right
} oled_menu_el_t;

typedef struct oled_menu {
    char *header_string; // Unselectable header shown on first row/page
    oled_menu_el_t *elements;
    oled_menu_action_t back_action; // When pushing joystick to left. Same for all elements in menu
    uint8_t num_elements;
    uint8_t selected_idx; // Index of selected menu element in elements-array
} oled_menu_t;


void oled_menu_navigate_up();
void oled_menu_navigate_down();
void oled_menu_navigate_left();
void oled_menu_navigate_right();

// Selection functions for menu elements
// Prefer to use these over manually calling the functions manually, as these check if the elements are not NULL
void oled_menu_select(oled_menu_el_t element);
void oled_menu_back(oled_menu_el_t element);

// Draws the menu to the buffer
void draw_oled_menu(oled_menu_t *menu, uint8_t *buffer);


// Project specific
void oled_menu_init(uint8_t * buffer);

#endif /* OLED_MENU_H */