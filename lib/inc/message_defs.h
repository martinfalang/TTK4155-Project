#ifndef MESSAGE_DEFS_H
#define MESSAGE_DEFS_H

typedef enum can_msg_type {
    CTRL_SID = 345, // Controller / joystick / slider data // TODO: Set actual value
    START_GAME_SID = 234, // TODO: Set actual value
    STOP_GAME_SID = 123, // TODO: Set actual value
    SCORE_SID = 100,
    CALIBRATE_SID = 456, // TODO: Set actual value // For running the calibration routine for the position controller
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

#endif /* MESSAGE_DEFS_H */