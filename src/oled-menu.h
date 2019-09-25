/*
    Menu framework for use with OLED screen
*/

#ifndef OLED_MENU_H
#define OLED_MENU_H

#include <stdint.h>

typedef struct oled_menu_el {
    char *element_text;
    uint8_t text_length; // Length of element_text
    void (*on_select)(void);
    void (*on_back)(void);
} oled_menu_el_t;

typedef struct oled_menu {
    char *header_string; // Unselectable header shown on first row/page
    uint8_t header_length; // Lenght of header_string
    oled_menu_el_t *elements;
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