#ifndef NODE1_GAME_H
#define NODE1_GAME_H

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Handles printing the score to the buffer
 * 
 */

void game_start(void);
void game_stop(void);

uint16_t game_get_score(void);
void game_set_score(uint16_t new_score);

void game_ir_beam_broken(void);

bool game_is_playing(void);

#endif  /* NODE1_GAME_H */