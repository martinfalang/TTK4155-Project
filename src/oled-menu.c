#include "oled-menu.h"

void oled_menu_navigate_up();
void oled_menu_navigate_down();
void oled_menu_navigate_left();
void oled_menu_navigate_right();

void oled_menu_select(oled_menu_el_t element);
void oled_menu_back(oled_menu_el_t element);

// Helper functions to initialize menu system
oled_menu_el_t get_test_element(void) {
    // Returns a test element that should turn the led on and off
    oled_menu_el_t test_element;

    test_element.eleme
}

oled_menu_t get_main_menu(void) {
    oled_menu_t main_menu;

    const char * header_string = "Ping Pong";

    main_menu.header_string = &header_string;
    main_menu.header_length = 9;

    const num_main_menu_elements = 1;
    oled_menu_el_t main_menu_elements[num_main_menu_elements];

    return main_menu
}

void init_oled_menu(void) {
    oled_menu_t main_menu;
}