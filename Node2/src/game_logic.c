
#include "game_logic.h"
#include "ir.h"
#include "solenoid.h"

#include <stdio.h>

int solenoid_cmd_prev = 0;
bool playing = false;

void game_init(game_difficulty_t difficulty, pid_t *motor_pid) {    
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
            // TODO: figure these out
            kp = 2.3;
            ki = 0.5;
            kd = 0.3;
            printf("Difficulty MEDIUM\n");            
            break;
        case HARD:
            // Tune pid with bad settings (oscillations)
            // TODO: figure these out
            kp = 2.3;
            ki = 0.5;
            kd = 0.3;
            printf("Difficulty HARD\n");
            break;
    }

    pid_init(motor_pid, kp, ki, kd, motor_pid->T, motor_pid->output_maximum, 
                                        motor_pid->output_minimum);
    playing = true;
}

void game_play(const can_msg_t *input_data, pid_t *motor_pos_pid) {

    if (!playing)
        return;

    // Solenoid logic
    if (input_data->data[0] == 2 && solenoid_cmd_prev != input_data->data[0]) {
        solenoid_cmd_prev = input_data->data[0];
        solenoid_give_pulse();
    }
    else if (input_data->data[0] != 2) {
        solenoid_cmd_prev = input_data->data[0];
    }

    // Control position of motor carrage
    int16_t pos_ref = input_data->data[5] * 10;
    motor_pos_pid->setpoint = pos_ref;
    printf("R: %d\tPos: %d\tU: %d\te: %d\n", (int)pos_ref, 
                (int)motor_pos_pid->measurement, (int)motor_pos_pid->output, 
                (int)motor_pos_pid->current_error);

    // Servo motor logic
    // pwm_set_duty_cycle(degrees);

    // IR beam logic
    if (ir_beam_broken()) {
        can_msg_t ir_broken;
        ir_broken.sid = 111;
        ir_broken.length = 0;
        can_send(&ir_broken);
        game_over();
    }
} 


void game_over(void) {
    playing = false;
    printf("Game over!\n");
    pid_stop_timer();
    can_msg_t end_of_game;
    end_of_game.sid = 123;
    end_of_game.length = 0;
    can_send(&end_of_game);
    // TODO: do whatever's gonna happen when game ends in this function
}