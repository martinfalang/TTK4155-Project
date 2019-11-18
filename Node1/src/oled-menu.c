
////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////

#include "../../lib/inc/defines.h"

#include <avr/interrupt.h>
#include <util/delay.h>         // for delay_ms

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <avr/pgmspace.h>

#include "../../lib/inc/can.h"
#include "../../lib/inc/message_defs.h"
#include "oled-menu.h"
#include "joystick.h"
#include "touch.h"
#include "oled-buffer.h"
#include "oled.h"
#include "game.h"
#include "buzzer.h"
#include "songs/star_wars.h"
#include "pictures/star_wars_picture_128x32.h"
#include "highscore.h"

////////////////////////////////////////////////////////////////////////////////
// Defines
////////////////////////////////////////////////////////////////////////////////

#define NUM_MAIN_MENU_ELEMENTS          4
#define NUM_SETTINGS_MENU_ELEMENTS      2
#define NUM_HIGHSCORE_ELEMENTS          NUM_HIGHSCORES
#define NUM_DIFFICULTY_MENU_ELEMENTS    3
#define NUM_INGAME_MENU_ELEMENTS        7
#define NUM_GAME_OVER_MENU_ELEMENTS     7

////////////////////////////////////////////////////////////////////////////////
// Private variables
////////////////////////////////////////////////////////////////////////////////

static oled_menu_t *p_current_menu;
static oled_menu_t main_menu;
static oled_menu_t highscore_menu;
static oled_menu_t settings_menu;
static oled_menu_t difficulty_menu;
static oled_menu_t ingame_menu;
static oled_menu_t game_over_menu;

struct oled_menu_elements {
    oled_menu_el_t main_menu_elements[NUM_MAIN_MENU_ELEMENTS];
    oled_menu_el_t difficulty_menu_elements[NUM_DIFFICULTY_MENU_ELEMENTS];
    oled_menu_el_t setting_menu_elements[NUM_SETTINGS_MENU_ELEMENTS];
    oled_menu_el_t highscore_menu_elements[NUM_HIGHSCORE_ELEMENTS];
    oled_menu_el_t ingame_menu_elements[NUM_INGAME_MENU_ELEMENTS];
    oled_menu_el_t game_over_menu_elements[NUM_GAME_OVER_MENU_ELEMENTS];
    
};

typedef struct oled_menu_elements oled_menu_elements_t;

static oled_menu_elements_t *_elements;

static joy_btn_dir_t prev_dir; 
static uint16_t prev_score = 0;

////////////////////////////////////////////////////////////////////////////////
// Private function declarations
////////////////////////////////////////////////////////////////////////////////

void draw_oled_menu(oled_menu_t *menu, uint8_t *buffer);

void _menu_init_menus(void);
oled_menu_action_t _menu_get_empty_action(void);
oled_menu_action_t _menu_create_menu_ptr_action(oled_menu_t *p_menu);
oled_menu_action_t _menu_create_func_ptr_action(void *p_func);
oled_menu_el_t _menu_create_element(char *text, oled_menu_action_t action);
oled_menu_el_t _menu_create_empty_element();
void _menu_perform_action(oled_menu_action_t action);
void _update_highscores_menu(void);
void _insert_new_highscore_test(void);

void _start_game(uint8_t difficulty);
void _stop_game(void);


const static can_msg_t _calibrate_msg = {
    .sid = CALIBRATE_SID, 
    .length = 0 };

////////////////////////////////////////////////////////////////////////////////
// Public functions
////////////////////////////////////////////////////////////////////////////////

void oled_menu_init(void) {
    _menu_init_menus();
    p_current_menu = &main_menu;

    prev_dir = NEUTRAL;

    draw_oled_menu(p_current_menu, OLED_BUFFER_BASE);
    oled_draw_screen(OLED_BUFFER_BASE);
}

void oled_menu_update(void) {
    joy_btn_dir_t dir = joystick_get_direction();
    bool should_update = false;

    bool in_playing_menu = p_current_menu == &ingame_menu 
                            || p_current_menu == &game_over_menu;


    if (dir == prev_dir && !in_playing_menu) {
        // If not playing and no new input is given, return
        // Cannot return in playing menu, as we might want to
        // update the score
        return;
    }

    // Do menu navigation and actions based on joystick input
    switch (dir)
    {
    case RIGHT:
        _menu_perform_action(
            p_current_menu->elements[p_current_menu->selected_idx].select_action);
            should_update = true;
        break;
    case LEFT:
            _menu_perform_action(p_current_menu->back_action);
            should_update = true;
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
        should_update = true;
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
        should_update = true;
        break;
    }

    prev_dir = dir;
    

    if (p_current_menu == &ingame_menu) {
        
        uint16_t new_score = game_get_score();
        
        if (prev_score != new_score || new_score == 0) {
            // Print the score if in game and it has changed since last time
            sprintf(ingame_menu.elements[1].element_text, "Score: %i", new_score);
            should_update = true;
        }
        touch_btn_t buttons = touch_read_btns();

        if (!game_is_playing() || buttons.left && buttons.right) {
            // Update the score in game over-menu
            sprintf(game_over_menu.elements[1].element_text, "Score: %i", new_score);
            p_current_menu = &game_over_menu;
            should_update = true;
            game_stop();
            _update_highscores_menu();
        }
    
        prev_score = new_score;
    }

    if (should_update) {
        // Only update the screen if something has changed
        draw_oled_menu(p_current_menu, OLED_BUFFER_BASE);
        oled_draw_screen(OLED_BUFFER_BASE);
    }

}

////////////////////////////////////////////////////////////////////////////////
// Private functions
////////////////////////////////////////////////////////////////////////////////

// Action functions

void _start_game_easy(void) {
    game_start(DIFF_EASY);
    p_current_menu = &ingame_menu;
}

void _start_game_medium(void) {
    game_start(DIFF_MEDIUM);
    p_current_menu = &ingame_menu;

}

void _start_game_hard(void) {
    game_start(DIFF_HARD);
    p_current_menu = &ingame_menu;
}

void _play_star_wars(void)  {
    oled_buffer_clear_screen(OLED_BUFFER_BASE);
    oled_buffer_draw_picture(STAR_WARS_PICTURE_COLUMNS, STAR_WARS_PICTURE_PAGES, 
                             starwars_picture_128x32, 0, 1, OLED_BUFFER_BASE);
    oled_draw_screen(OLED_BUFFER_BASE);

    buzzer_init();
    buzzer_play_song_P(star_wars_melody, star_wars_note_types, 
                    STAR_WARS_LENGTH, STAR_WARS_BAR_LENGTH_MS);
}

void _reset_highscores_and_update(void) {
    highscore_reset();
    _update_highscores_menu();
}

void _send_calibrate(void) {
    can_send(&_calibrate_msg);
}

// Menu functions

void _menu_init_menus(void) {
    // Set menu elements pointer to point to external memory
    _elements = (oled_menu_elements_t *) OLED_MENU_ELEMENTS_BASE;

    // Set up main menu
    main_menu.num_elements = NUM_MAIN_MENU_ELEMENTS;
    strcpy(main_menu.header_string, "Main Menu");
    main_menu.selected_idx = 0;
    main_menu.back_action = _menu_get_empty_action();

    main_menu.elements = _elements->main_menu_elements;

    main_menu.elements[0] = _menu_create_element("Play Game", _menu_create_menu_ptr_action(&difficulty_menu));
    main_menu.elements[1] = _menu_create_element("Highscores", _menu_create_menu_ptr_action(&highscore_menu));
    main_menu.elements[2] = _menu_create_element("Settings", _menu_create_menu_ptr_action(&settings_menu));
    main_menu.elements[3] = _menu_create_element("Play Star Wars", _menu_create_func_ptr_action(&_play_star_wars));

    // Set up submenus
    // Set up highscores "menu"
    strcpy(highscore_menu.header_string, "Highscores");
    highscore_menu.num_elements = NUM_HIGHSCORE_ELEMENTS;
    highscore_menu.back_action = _menu_create_menu_ptr_action(&main_menu);
    highscore_menu.selected_idx = 0;

    highscore_menu.elements = _elements->highscore_menu_elements;

    for (uint8_t i = 0; i < NUM_HIGHSCORE_ELEMENTS; ++i) {
        // Should not do anything when "selecting a score"
        highscore_menu.elements[i] = _menu_create_element("", _menu_get_empty_action()); 
    }

    _update_highscores_menu(); // Generates strings and prints them to the menu

    // Set up settings menu
    strcpy(settings_menu.header_string, "Settings");
    settings_menu.num_elements = NUM_SETTINGS_MENU_ELEMENTS;
    settings_menu.back_action = _menu_create_menu_ptr_action(&main_menu);
    settings_menu.selected_idx = 0;

    settings_menu.elements = _elements->setting_menu_elements;

    settings_menu.elements[0] = _menu_create_element("Calibrate position", _menu_create_func_ptr_action(&_send_calibrate));
    settings_menu.elements[1] = _menu_create_element("Reset highscores", _menu_create_func_ptr_action(&_reset_highscores_and_update));

    // Set up difficulties menu
    strcpy(difficulty_menu.header_string, "Difficulty");
    difficulty_menu.num_elements = NUM_DIFFICULTY_MENU_ELEMENTS;
    difficulty_menu.back_action = _menu_create_menu_ptr_action(&main_menu);
    difficulty_menu.selected_idx = 0;

    difficulty_menu.elements = _elements->difficulty_menu_elements;

    difficulty_menu.elements[0] = _menu_create_element("Easy", _menu_create_func_ptr_action(&_start_game_easy));
    difficulty_menu.elements[1] = _menu_create_element("Medium", _menu_create_func_ptr_action(&_start_game_medium));
    difficulty_menu.elements[2] = _menu_create_element("Hard", _menu_create_func_ptr_action(&_start_game_hard));


    // Set up ingame menu
    strcpy(ingame_menu.header_string, "Playing...");
    ingame_menu.num_elements = NUM_INGAME_MENU_ELEMENTS;
    ingame_menu.back_action = _menu_get_empty_action();
    ingame_menu.selected_idx = 0;

    ingame_menu.elements = _elements->ingame_menu_elements;

    ingame_menu.elements[0] = _menu_create_empty_element();
    ingame_menu.elements[1] = _menu_create_empty_element();

    ingame_menu.elements[2] = _menu_create_empty_element();
    ingame_menu.elements[3] = _menu_create_empty_element();
    ingame_menu.elements[4] = _menu_create_empty_element();

    ingame_menu.elements[5] = _menu_create_element("Press both touch", _menu_get_empty_action());
    ingame_menu.elements[6] = _menu_create_element("buttons to quit!", _menu_get_empty_action());


    // Set up game over menu
    strcpy(game_over_menu.header_string, "Game over");
    game_over_menu.num_elements = NUM_GAME_OVER_MENU_ELEMENTS;
    game_over_menu.back_action = _menu_create_menu_ptr_action(&main_menu);
    
    game_over_menu.selected_idx = 5;

    game_over_menu.elements = _elements->game_over_menu_elements;

    game_over_menu.elements[0] = _menu_create_element("", _menu_create_menu_ptr_action(&highscore_menu));
    game_over_menu.elements[1] = _menu_create_element("", _menu_create_menu_ptr_action(&highscore_menu));
    game_over_menu.elements[2] = _menu_create_element("", _menu_create_menu_ptr_action(&highscore_menu));
    game_over_menu.elements[3] = _menu_create_element("", _menu_create_menu_ptr_action(&highscore_menu));
    game_over_menu.elements[4] = _menu_create_element("", _menu_create_menu_ptr_action(&highscore_menu));

    game_over_menu.elements[5] = _menu_create_element("Press right to", _menu_create_menu_ptr_action(&highscore_menu));
    game_over_menu.elements[6] = _menu_create_element("go to highscore", _menu_create_menu_ptr_action(&highscore_menu));
}

void _update_highscores_menu(void) {
    for (uint8_t i = 0; i < NUM_HIGHSCORE_ELEMENTS; ++i) {
        highscore_print_score(highscore_menu.elements[i].element_text, i + 1); // Place starts on 1 (1st place)
    }
}

void draw_oled_menu(oled_menu_t *menu, uint8_t *buffer) {
    // Clear the buffer
    oled_buffer_clear_screen(buffer);

    // Draw the header
    oled_buffer_print_string(menu->header_string, LARGE, 0, buffer);

    // Draw the elements
    char row_string[32] = "";

    const char *selected_marker = "> ";
    const char *not_selected_marker = "  ";

    for (uint8_t i = 0; i < menu->num_elements; ++i)
    {
        strcpy(row_string, "");

        bool is_selected = menu->selected_idx == i;
        bool in_menu_without_marker = p_current_menu == &ingame_menu 
                                    || p_current_menu == &game_over_menu
                                    || p_current_menu == &highscore_menu;
                                    
        
        if (is_selected && !in_menu_without_marker) {
            // Add "> " before the string
            strcat(row_string, selected_marker);
        }
        else {
            // Add "  " before the string
            strcat(row_string, not_selected_marker);
        }

        strcat(row_string, menu->elements[i].element_text);

        // Print the string to the buffer
        oled_buffer_print_string(row_string, MEDIUM, i + 1, buffer);
    }
}

oled_menu_action_t _menu_get_empty_action(void) {
    // Returns an empty action
    oled_menu_action_t action;
    action.ptr.p_menu = NULL;
    action.is_func_ptr = false;

    return action;
}

oled_menu_action_t _menu_create_menu_ptr_action(oled_menu_t *p_menu) {
    oled_menu_action_t action;

    action.is_func_ptr = false;
    action.ptr.p_menu = p_menu;

    return action;
}

oled_menu_action_t _menu_create_func_ptr_action(void *p_func) {
    oled_menu_action_t action;
    action.is_func_ptr = true;
    action.ptr.p_menu = p_func;

    return action;
}

oled_menu_el_t _menu_create_element(char *text, oled_menu_action_t action) {
    oled_menu_el_t element;

    strcpy(element.element_text, text);
    element.select_action = action;

    return element;
}

oled_menu_el_t _menu_create_empty_element() {
    oled_menu_el_t element;

    // Set the string to be empty
    strcpy(element.element_text, "");
    // Set the action to do nothing
    element.select_action = _menu_get_empty_action();

    return element;
}

void _menu_perform_action(oled_menu_action_t action) {
    if (action.is_func_ptr && action.ptr.p_func != NULL) {
        // Call function in function pointer
        action.ptr.p_func();
    }
    else if (action.ptr.p_menu != NULL) {
        // Change current menu to the pointer in the performed action if it is not NULL
        p_current_menu = action.ptr.p_menu;
    }
}