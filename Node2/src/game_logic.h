/**
 * @file game_logic.h
 * @author Kristian Brudeli
 *         Martin Falang
 *         Eirik Flemsæter Falck
 * @brief Implements functions for the game logic on Node 2. 
 * @version 0.1
 * @date 2019-11-18
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <stdbool.h>

#include "../../lib/inc/can.h"
#include "pid.h"


/**
 * @brief Possible game difficulties
 * 
 */
typedef enum game_difficulty {
    EASY,
    MEDIUM,
    HARD
} game_difficulty_t;


/**
 * @brief 
 * 
 * @param difficulty 
 * @param motor_pid 
 */
void game_init(game_difficulty_t difficulty, pid_t *motor_pid);


/**
 * @brief 
 * 
 * @param input_data 
 * @param motor_pos_pid
 */
void game_play(const can_msg_t *input_data, pid_t *motor_pos_pid);

/**
 * @brief The set of commands that should run when the game ends
 * 
 */
void game_over();


#endif // GAME_LOGIC_H
