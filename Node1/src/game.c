#include "game.h"
#include "oled-buffer.h"
#include "oled-menu.h"
#include "../../lib/inc/can.h"
#include "../../lib/inc/message_defs.h"
#include "highscore.h"

static bool _is_playing = false;
static bool _in_game = false;
static uint16_t _score = 0;

static can_msg_t _start_game_msg = { .sid = START_GAME_SID, .length = 1 , .data[0] = 0};
const static can_msg_t _stop_game_msg = { .sid = STOP_GAME_SID, .length = 0 };


// TODO Update with enum
void game_start(uint8_t difficulty) {
    _is_playing = true;
    _in_game = true;

    // Reset score
    _score = 0;

    // Set difficulty
    _start_game_msg.data[DIFFICULTY_IDX] = difficulty;

    // Send message to node 2 to start game
    can_send(&_start_game_msg);
}

void game_stop(void) {
    if (_is_playing) {
        _is_playing = false;

        highscore_nominate(game_get_score());

        // Send message to node 2 to stop game
        can_send(&_stop_game_msg);
    }
}


bool game_is_playing(void) {
    return _is_playing;
}

uint16_t game_get_score(void) {
    return _score;
}


void game_set_score(uint16_t new_score) {
    _score = new_score;
}

bool game_in_game(void) {
    return _in_game;
}

void game_exit(void) {
    _in_game = false;
}