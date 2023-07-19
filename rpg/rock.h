#ifndef __ROCK_H__
#define __ROCK_H__

#include "entity.h"
#include "coordinate.h"
#include "obstacle.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>

class rock : public obstacle{
public:

    rock(double x, double y)
    {
        position.set(x, y);
        hitbox_start.set(x, y);
        hitbox_end.set(x + ROCK_SIZE, y + ROCK_SIZE);
        is_destroyed_by_magic = false;
        is_destroyed_by_fire = false;
        can_player_pass = false;
    }

    void draw(coordinate camera) override
    {
        if(!exist)
            return;
        if(position.x + ROCK_SIZE < camera.x || position.y + ROCK_SIZE < camera.y)
            return;
        if(position.x >= camera.x + WINDOW_WIDTH || position.y >= camera.y + WINDOW_HEIGHT)
            return;

        int draw_x = position.x - camera.x;
        int draw_y = position.y - camera.y;
        al_draw_filled_rectangle(draw_x, draw_y, draw_x + ROCK_SIZE, draw_y +  ROCK_SIZE, ROCK_COLOR);
    }
};

#endif //__ROCK_H__
