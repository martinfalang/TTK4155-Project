#ifndef PONG_H
#define PONG_H

#include <stdbool.h>


#ifdef COMPUTER
void pong_print_game(void);
#endif


typedef struct pong_object {
    int x;  // x pos
    int y;  // y pos
    int w;  // width
    int h;  // height
    int dir;  // direction of travel
} pong_object_t;

typedef pong_object_t pong_ball_t;
typedef pong_object_t pong_paddle_t;


bool pong_check_collision(pong_object_t obj1, pong_object_t obj2);



#endif  // PONG_H