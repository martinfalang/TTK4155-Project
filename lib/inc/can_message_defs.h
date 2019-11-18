/**
 * @file can_message_defs.h
 * @author Kristian Brudeli
 *         Martin Falang
 *         Eirik Flemsæter Falck
 * @brief Defines useful enums for sending CAN messages.
 * @version 0.1
 * @date 2019-11-18
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef can_message_defs_H
#define can_message_defs_H

////////////////////////////////////////////////////////////////////////////////
// Enums
////////////////////////////////////////////////////////////////////////////////

typedef enum can_msg_type {
    IO_DATA_SID = 0,
    START_GAME_SID = 1,
    STOP_GAME_SID = 2,
    SCORE_SID = 3,
    CALIBRATE_SID = 4,
} can_msg_type_t;

// Definitions of messages corresponding to different message types 
typedef enum can_ctrl_msg_idx {
    JOY_DIR_IDX = 0,
    JOY_POS_X_IDX,
    JOY_POS_Y_IDX,
    BTNS_LEFT_IDX,
    BTNS_RIGHT_IDX,
    SLIDER_LEFT_IDX,
    SLIDER_RIGHT_IDX,
} can_ctrl_msg_idx_t;

typedef enum can_start_msg_idx {
    DIFFICULTY_IDX = 0,
} can_start_msg_idx_t;

typedef enum can_sender {
    NODE1 = 1,
    NODE2 = 2
} can_sender_t;

typedef enum can_stop_game_msg {
    SENDER_IDX
} can_stop_game_msg_t;

#endif /* can_message_defs_H */