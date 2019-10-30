#include "pong.h"
#include <stdio.h>  // printf
#include <stdlib.h>  // system
#include <time.h>  // nanosleep

/* -------- PRIVATE VARIABLES ----------- */
#define __N_PONG_OBJS 3

char _board[PONG_BOARD_WIDTH * PONG_BOARD_HEIGHT];
pong_object_t _ball;
pong_object_t _paddle_left;
pong_object_t _paddle_right;
pong_object_t *_objarr[__N_PONG_OBJS];


bool new_tick = false;
int ticks = 0;
int speed = 100000000;

/* ---------- PRIVATE FUNCTIONS ----------- */

int _board_get_xy_index(int x, int y) {
    return y * PONG_BOARD_WIDTH + x;
}


void _update_gametick(void) {
    new_tick = true;
    static struct timespec ts;
    ts.tv_nsec = 10000000;
    ts.tv_sec = 0;
    nanosleep(&ts, NULL);
}


void _clear_board(void) {
    for (int i = 0; i < PONG_BOARD_WIDTH * PONG_BOARD_HEIGHT; ++i) {
        _board[i] = ' ';
    }
}


void _clear_term(void) {
    // printf("\033[0;0H\033[2J");
    system("clear");
}


/* ---------- PUBLIC FUNCTOINS ---------- */
void pong_init(int ball_width, int ball_height, int paddle_height) {
    _ball.w = ball_width;
    _ball.h = ball_height;
    _ball.x = PONG_BOARD_WIDTH / 2 - ball_width / 2;
    _ball.y = PONG_BOARD_HEIGHT / 2 - ball_height / 2;
    _ball.dirx = 1;
    _ball.diry = 0;

    _paddle_left.w = PONG_PADDLE_WIDTH;
    _paddle_left.h = paddle_height;
    _paddle_left.x = 0 + PONG_PADDLE_EDGE_PADDING;
    _paddle_left.y = PONG_BOARD_HEIGHT / 2 - paddle_height / 2;
    _paddle_left.dirx = 0;
    _paddle_left.diry = 0;

    _paddle_right.w = PONG_PADDLE_WIDTH;
    _paddle_right.h = paddle_height;
    _paddle_right.x = PONG_BOARD_WIDTH - PONG_PADDLE_EDGE_PADDING - 1;
    _paddle_right.y = PONG_BOARD_HEIGHT / 2 - paddle_height / 2;
    _paddle_right.dirx = 0;
    _paddle_right.diry = 0;


    _objarr[0] = &_ball;
    _objarr[1] = &_paddle_left;
    _objarr[2] = &_paddle_right;


    _clear_board();
}


void pong_play_game(void) {
    while (1) {
        _update_gametick();

        if (new_tick) {
            pong_update_objects_position(_objarr);
            
            if (pong_check_collision(&_ball, &_paddle_left)) {
                printf("LEFT!");
                _ball.dirx = 1;
            }
            if (pong_check_collision(&_ball, &_paddle_right)) {
                printf("RIGHT!");
                _ball.dirx = -1;
            }

            pong_print_game();
        }
    }
    
}


void pong_update_objects_position(pong_object_t ** objarr) {
    for (int i = 0; i < __N_PONG_OBJS; ++i) {
        objarr[i]->x += objarr[i]->dirx;
        objarr[i]->y += objarr[i]->diry;
    }
}


bool pong_check_collision(const pong_object_t *obj1, const pong_object_t *obj2) {
    int left1 = obj1->x;
    int right1 = obj1->x + obj1->w;
    int top1 = obj1->y;
    int bottom1 = obj1->y + obj1->h;

    int left2 = obj2->x;
    int right2 = obj2->x + obj2->w;
    int top2 = obj2->y;
    int bottom2 = obj2->y + obj2->h;


	if (left1 > right2) {
		return false;
	}

	if (right1 < left2) {
		return false;
	}

	if (top1 > bottom2) {
		return false;
	}

	if (bottom1 < top2) {
		return false;
	}

	return true;
}


void pong_print_obj_to_board(const pong_object_t *obj) {
    for (int i = 0; i < obj->w; ++i) {
        for (int j = 0; j < obj->h; ++j) {
            _board[_board_get_xy_index(obj->x + i, obj->y + j)] = '*';
        }
    }
}


void pong_print_objects_to_board(const pong_object_t ** objarr) {
    for (int k = 0; k < __N_PONG_OBJS; ++k) {
        pong_print_obj_to_board(objarr[k]);
    }
}


void pong_print_game(void) {
    _clear_term();
    _clear_board();
    pong_print_objects_to_board((const pong_object_t **)_objarr);

    for (int y = 0; y < PONG_BOARD_HEIGHT; ++y) {
        for (int x = 0; x < PONG_BOARD_WIDTH; ++x) {
            printf("%c", _board[_board_get_xy_index(x, y)]);
        }
        printf("\n");
    }
}





