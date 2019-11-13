#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "../../lib/inc/can.h"
#include "pid.h"

#include <stdbool.h>

typedef enum game_difficulty {
    EASY,
    MEDIUM,
    HARD
} game_difficulty_t;


void game_init(game_difficulty_t difficulty, pid_t *motor_pid);


/**
 * @brief 
 * 
 * @param input_data 
 * @param motor_pos_pid
 */
void game_play(const can_msg_t *input_data, pid_t *motor_pos_pid);


void game_over();


#endif // GAME_LOGIC_H
