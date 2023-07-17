#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "entity.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>

class enemy : public entity {
protected:
    int health_points;
    int fire_damage;
    int magic_damage;
    int size;
    ALLEGRO_COLOR color;

public:
    void hit_by(int type)
    {
        if(type == FIRE_TYPE)
        {
            health_points -= fire_damage;
        }
        if(type == MAGIC_TYPE)
        {
            health_points -= magic_damage;
        }
        if(health_points <= 0)
            kill();
    }
    void draw(coordinate camera)
    {
        if(!exist)
            return;
        if(position.x < camera.x || position.y < camera.y)
            return;
        if(position.x >= camera.x + WINDOW_WIDTH || position.y >= camera.y + WINDOW_HEIGHT)
            return;
        int draw_x = position.x - camera.x;
        int draw_y = position.y - camera.y;
        al_draw_filled_circle(draw_x, draw_y, size / 2, color);
    }
};

#endif //__ENEMY_H__
