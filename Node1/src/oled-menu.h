/*
    Menu framework for use with OLED screen
*/
#ifndef OLED_MENU_H
#define OLED_MENU_H

////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <stdbool.h>

////////////////////////////////////////////////////////////////////////////////
// Forward declarations
////////////////////////////////////////////////////////////////////////////////

typedef struct oled_menu oled_menu_t; 

////////////////////////////////////////////////////////////////////////////////
// Structs and unions
////////////////////////////////////////////////////////////////////////////////

typedef union oled_menu_action_ptr {
    oled_menu_t *p_menu;
    void (* p_func)(void);
} oled_menu_action_ptr_t;

typedef struct ole_menu_action {
    oled_menu_action_ptr_t ptr;
    bool is_func_ptr; // True if ptr is a function pointer, false if it is a oled_menu_t pointer
} oled_menu_action_t;

typedef struct oled_menu_el {
    char element_text[20];
    oled_menu_action_t select_action; // When pushing joystick to right
} oled_menu_el_t;

typedef struct oled_menu {
    char header_string[20];
    oled_menu_el_t *elements;
    oled_menu_action_t back_action; // When pushing joystick to left. Same for all elements in menu
    uint8_t num_elements;
    uint8_t selected_idx; // Index of selected menu element in elements-array
} oled_menu_t;

////////////////////////////////////////////////////////////////////////////////
// Function declarations
////////////////////////////////////////////////////////////////////////////////

void oled_menu_init(void);
void oled_menu_update(void);

#endif /* OLED_MENU_H */