#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <stdint.h>

#define NUM_HIGHSCORES 5

/**
 * @brief Initializes the highscore list to a predefined state
 * 
 */
void highscore_reset(void);

/**
 * @brief Gets the score associated with the given place, and -1 if it doesn't
 *        exist.
 *        E.g. highscore_get(1) returns the first place, 
 *        highscore_get(3) the third place etc.
 * 
 * @param place 
 * @return uint16_t 
 */
uint16_t highscore_get(uint8_t place);

/**
 * @brief Writes the score of given place to the string out. Guaranteed to not be
 *        longer than HIGHSCORE_STR_MAX_LENGTH
 * 
 * @param out 
 * @param max_length 
 */
void highscore_print_score(char * out, uint8_t place);

/**
 * @brief Places the high score in the list if it is good enough.
 * 
 * @param score The candidate score
 * @return uint8_t The placement in the high score list if good enough. 
 *                 0 if it is not good enough
 */
uint8_t highscore_nominate(uint16_t score);

#endif  /* HIGHSCORE_H */