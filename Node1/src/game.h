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


/**
 * @brief Handles when the user wants to exit the game before the IR beam
 *        is broken, normally by pressing the left touch button in-game.
 * 
 */
void game_stop(void);


/**
 * @brief Sets the new score
 * 
 * @param new_score New score
 */
uint16_t game_get_score(void);

/**
 * @brief Gets the current score
 * 
 * @return uint16_t The current score
 */
void game_set_score(uint16_t new_score);

void game_ir_beam_broken(void);

/**
 * @brief Returns whether one is currently in a game
 *
 */
bool game_is_playing(void);


#endif  /* NODE1_GAME_H */