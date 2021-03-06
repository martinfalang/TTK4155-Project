////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////

#include "game_logic.h"
#include "ir.h"
#include "solenoid.h"
#include "servo.h"

#include "../../lib/inc/timer.h"
#include "../../lib/inc/can_message_defs.h"

#include <stdio.h>

////////////////////////////////////////////////////////////////////////////////
// Defines
////////////////////////////////////////////////////////////////////////////////

#define PRINT_PID_DATA  1

////////////////////////////////////////////////////////////////////////////////
// Private variables
////////////////////////////////////////////////////////////////////////////////

int solenoid_cmd_prev = 0;
bool playing = false;
uint8_t score = 0;

can_msg_t endofgame_msg = {
    .length = 1,
    .sid = STOP_GAME_SID,
    .data[0] = 0
};


////////////////////////////////////////////////////////////////////////////////
// Public functions
////////////////////////////////////////////////////////////////////////////////

void game_init(game_difficulty_t difficulty, pid_t *motor_pid) {

    score = 0;

    float kp;
    float ki;
    float kd;

    switch (difficulty) {
        default:
        case EASY:
            // Tune pid with best settings
            kp = 2.3;
            ki = 0.5;
            kd = 0.3;
            printf("Difficulty EASY\n");
            break;
        case MEDIUM:
            // Tune pid with decent settings (slow)
            kp = 1.5;
            ki = 0.5;
            kd = 0.5;
            printf("Difficulty MEDIUM\n");            
            break;
        case HARD:
            // Tune pid with bad settings (oscillations)
            kp = 2.7;
            ki = 0.5;
            kd = 0.1;
            printf("Difficulty HARD\n");
            break;
    }

    pid_init(motor_pid, kp, ki, kd, motor_pid->T, motor_pid->output_maximum, 
             motor_pid->output_minimum, motor_pid->error_deadzone);
    playing = true;
}


void game_play(const can_msg_t *input_data, pid_t *motor_pos_pid) {
    if (!playing)
        return;

    if (timer_get_1Hz_timeout()) {
        score++;
    }

    // Solenoid logic
    if (input_data->data[JOY_DIR_IDX] == 2 && 
            solenoid_cmd_prev != input_data->data[JOY_DIR_IDX]) {
        solenoid_cmd_prev = input_data->data[JOY_DIR_IDX];
        solenoid_give_pulse();
    }
    else if (input_data->data[JOY_DIR_IDX] != 2) {
        solenoid_cmd_prev = input_data->data[JOY_DIR_IDX];
    }

    // Control position of motor carrage
    int16_t pos_ref = input_data->data[SLIDER_LEFT_IDX] * 10;
    motor_pos_pid->setpoint = pos_ref;

#if PRINT_PID_DATA
    printf("R: %d\tPos: %d\tU: %d\te: %d\n", (int)pos_ref, 
                (int)motor_pos_pid->measurement, (int)motor_pos_pid->output, 
                (int)motor_pos_pid->current_error);
#endif // PRINT_PID_DATA

    // Servo motor logic
    int16_t degrees = input_data->data[SLIDER_RIGHT_IDX];
    servo_set_angle(degrees);

    can_msg_t score_msg = {
        .sid = SCORE_SID,
        .length = 1,
        .data[0] = score
    };

    can_send(&score_msg);

    // IR beam logic
    if (ir_beam_broken()) {
        ir_reset();
        endofgame_msg.data[0] = 1;
        game_over();
    }


} 


void game_over(void) {
    if (!playing)
        return;

    playing = false;
    printf("Game over!\n");
    pid_stop_timer();
    can_send(&endofgame_msg);
}
