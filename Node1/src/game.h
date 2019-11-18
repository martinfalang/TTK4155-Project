/**
 * @file game.h
 * @author Kristian Brudeli
 *         Martin Falang
 *         Eirik Flemsæter Falck
 * @brief Implements functions relevant for the game logic on Node 1. 
 * @version 0.1
 * @date 2019-11-18
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef NODE1_GAME_H
#define NODE1_GAME_H

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Handles printing the score to the buffer
 * 
 */

// TODO Update with enum
void game_start(uint8_t difficulty);
void game_stop(void);

uint16_t game_get_score(void);
void game_set_score(uint16_t new_score);

void game_ir_beam_broken(void);

bool game_is_playing(void);

#endif  /* NODE1_GAME_H */