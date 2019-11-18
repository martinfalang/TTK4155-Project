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


////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////

#include <stdbool.h>
#include <stdint.h>


////////////////////////////////////////////////////////////////////////////////
// Enums
////////////////////////////////////////////////////////////////////////////////

typedef enum difficulty {
    DIFF_EASY,
    DIFF_MEDIUM,
    DIFF_HARD
} difficulty_t;


////////////////////////////////////////////////////////////////////////////////
// Function declarations
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Starts the game from Node1's side
 * 
 * @param difficulty The difficulty to be played at
 */
void game_start(difficulty_t difficulty);

/**
 * @brief Stop the game either when game was canceled or
 *          game was over
 * 
 */
void game_stop(void);

/**
 * @brief Sets the new score
 * 
 * @param new_score New score
 */
void game_set_score(uint8_t new_score);

/**
 * @brief Gets the current score
 * 
 * @return uint16_t The current score
 */
uint8_t game_get_score(void);

/**
 * @brief Returns whether one is currently in a game
 *
 */
bool game_is_playing(void);

#endif  /* NODE1_GAME_H */