#ifndef PONG_H
#define PONG_H

#include <stdbool.h>


#ifdef COMPUTER
void clear_term(void);
void pong_print_game(void);
#endif


typedef struct pong_object {
    int x;  // x pos
    int y;  // y pos
    int w;  // width
    int h;  // height
    int dirx;  // direction of travel in x direction
    int diry;  // direction of travel in y direction
} pong_object_t;

typedef pong_object_t pong_ball_t;
typedef pong_object_t pong_paddle_t;

/**
 * @brief Check collision (i.e. overlap) between two pong objects
 * 
 * @param obj1 Object 1
 * @param obj2 Object 2
 * @return true If they overlap/have collidied
 * @return false If they don't overlap/haven't collided
 */
bool pong_check_collision(pong_object_t obj1, pong_object_t obj2);

/**
 * @brief Update all game objects' position
 * 
 * @param objarr 
 */
void pong_update_objects_position(pong_object_t[] objarr);


#endif  // PONG_H