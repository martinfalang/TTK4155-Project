#include "game.h"
#include "oled-buffer.h"
#include "oled-menu.h"
#include "can.h"

static bool _is_playing = false;
static uint16_t _score = 0;

const static can_msg_t _start_game_msg = { .sid = START_GAME_SID, .length = 0 };
const static can_msg_t _stop_game_msg = { .sid = STOP_GAME_SID, .length = 0 };


void game_start(void) {
    _is_playing = true;

    // Reset score
    _score = 0;

    // Send message to node 2 to start game
    can_send(&_start_game_msg);
}

/**
 * @brief Handles when the user wants to exit the game before the IR beam
 *        is broken, normally by pressing the left touch button in-game.
 * 
 */
void game_stop(void) {
    _is_playing = false;

    // Send message to node 2 to stop game
    can_send(&_stop_game_msg);
}

/**
 * @brief Returns whether one is currently in a game
 *
 */
bool game_is_playing(void) {
    return _is_playing;
}

/**
 * @brief Gets the current score
 * 
 * @return uint16_t The current score
 */
uint16_t game_get_score(void) {
    return _score;
}

/**
 * @brief Sets the new score
 * 
 * @param new_score New score
 */
void game_set_score(uint16_t new_score) {
    _score = new_score;
}
