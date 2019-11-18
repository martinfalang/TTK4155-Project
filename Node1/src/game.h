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

void game_ir_beam_broken(void);

/**
 * @brief Returns whether one is currently in a game
 *
 */
bool game_is_playing(void);


// TODO: Doxygen
bool game_in_game(void);

void game_exit(void);

#endif  /* NODE1_GAME_H */