#ifndef __BUSH_H__
#define __BUSH_H__

#include "entity.h"
#include "coordinate.h"
#include "obstacle.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <math.h>

class bush : public obstacle{
public:

    bush(double x, double y)
    {
        position.set(x, y);
        hitbox_start.set(x - BUSH_SIZE / 2, y - BUSH_SIZE / 2);
        hitbox_end.set(x + BUSH_SIZE / 2, y);
        is_destroyed_by_magic = false;
        is_destroyed_by_fire = true;
        can_player_pass = false;
    }

    void draw(coordinate camera) override
    {
        if(!exist)
            return;

        if(position.x + BUSH_SIZE < camera.x || position.y + BUSH_SIZE < camera.y)
            return;
        if(position.x >= camera.x + WINDOW_WIDTH || position.y >= camera.y + WINDOW_HEIGHT)
            return;

        int draw_x = position.x - camera.x;
        int draw_y = position.y - camera.y;
        al_draw_filled_pieslice(draw_x, draw_y, BUSH_SIZE / 2, M_PI,  M_PI, BUSH_COLOR);
    }

};

#endif //__BUSH_H__
