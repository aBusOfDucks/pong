#ifndef __PROJECTILE_H__
#define __PROJECTILE_H__

#include "const.h"
#include <iostream>
#include "coordinate.h"
#include <mutex>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include "entity.h"

class projectile{
public:

    std::mutex mutex_position;
    double x, y;
    double dx, dy;
    double speed = 1;
    int size = 1;
    ALLEGRO_COLOR color;
    int range = 10;
    int type = 3;

    projectile()
    {
        dx = 0;
        dy = 0;
    }

    projectile(coordinate camera, int mouse_x, int mouse_y)
    {
        x = camera.x + mouse_x;
        y = camera.y + mouse_y;
    }

    void move(entity ** entities)
    {
        std::unique_lock<std::mutex> lock(mutex_position);
        x += dx;
        y += dy;
        range--;
        coordinate hitbox_start(x - size / 2, y - size / 2);
        coordinate hitbox_end(x + size / 2, y + size / 2);
        for(int i = 0; i < MAX_ENTITIES; i++)
        {
            if(entities[i]->collide(hitbox_start, hitbox_end))
            {
                entities[i]->hit_by(type);
                destroy();
            }
        }
    }

    bool check()
    {
        if (range <= 0)
            return false;
        if(x < 0 || y < 0)
            return false;
        if(x >= MAP_WIDTH || y >= MAP_HEIGHT)
            return false;
        return true;
    }

    void draw(coordinate camera)
    {
        if(x < camera.x || y < camera.y)
            return;
        if(x >= camera.x + WINDOW_WIDTH || y >= camera.y + WINDOW_HEIGHT)
            return;
        int draw_x = x - camera.x;
        int draw_y = y - camera.y;
        al_draw_filled_circle(draw_x, draw_y, size / 2, color);
    }

    const void set(int new_x, int new_y, double new_dx, double new_dy)
    {
        x = new_x - size / 2;
        y = new_y - size / 2;
        dx = new_dx;
        dy = new_dy;
        double dis = sqrt(dx * dx + dy * dy);
        dx *= speed / dis;
        dy *= speed / dis;
    }

    projectile& operator=(projectile & other)
    {
        this->x = other.x;
        this->y = other.y;
        this->dx = other.dx;
        this->dy = other.dy;
        this->size = other.size;
        this->speed = other.speed;
        this->color = other.color;
        this->range = other.range;
        this->type = other.type;
        return *this;
    }

    void destroy()
    {
        range = 0;
    }
};

#endif //__PROJECTILE_H__
