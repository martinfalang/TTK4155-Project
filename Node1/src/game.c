////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////

#include "game.h"
#include "oled-buffer.h"
#include "oled-menu.h"
#include "../../lib/inc/can.h"
#include "../../lib/inc/can_message_defs.h"
#include "highscore.h"


////////////////////////////////////////////////////////////////////////////////
// Private functions
////////////////////////////////////////////////////////////////////////////////

static bool _is_playing = false;
static uint8_t _score = 0;

static can_msg_t _start_game_msg = { .sid = START_GAME_SID, .length = 1 , .data[0] = 0};
const static can_msg_t _stop_game_msg = { .sid = STOP_GAME_SID, .length = 0 };


////////////////////////////////////////////////////////////////////////////////
// Public functions
////////////////////////////////////////////////////////////////////////////////

void game_start(difficulty_t difficulty) {
    _is_playing = true;

    _score = 0;

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

uint8_t game_get_score(void) {
    return _score;
}

void game_set_score(uint8_t new_score) {
    _score = new_score;
}
