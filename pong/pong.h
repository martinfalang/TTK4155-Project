#ifndef PONG_H
#define PONG_H

#include <stdbool.h>


#define PONG_BOARD_WIDTH  128
#define PONG_BOARD_HEIGHT 64

#define PONG_PADDLE_WIDTH 2
#define PONG_PADDLE_EDGE_PADDING 1


typedef struct pong_object {
    int x;  // x pos
    int y;  // y pos
    int w;  // width
    int h;  // height
    int dirx;  // direction of travel in x direction
    int diry;  // direction of travel in y direction
} pong_object_t;


void pong_init(int ball_width, int ball_height, int paddle_height);
void pong_play_game(void);

void pong_print_obj_to_board(const pong_object_t *obj);
void pong_print_objects_to_board(const pong_object_t ** objarr);
void pong_print_game(void);

bool pong_check_collision(const pong_object_t *obj1, const pong_object_t *obj2);
void pong_update_objects_position(pong_object_t ** objarr);


#endif  // PONG_H