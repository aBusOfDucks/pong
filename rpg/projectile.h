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
    coordinate position;
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
        position.set(camera.x + mouse_x, camera.y + mouse_y);
    }

    void move(entity ** entities)
    {
        std::unique_lock<std::mutex> lock(mutex_position);
        position.change(dx, dy);
        range--;
        coordinate hitbox_start(position.x - size / 2, position.y - size / 2);
        coordinate hitbox_end(position.x + size / 2, position.y + size / 2);
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
        if(position.x < - size / 2 || position.y < - size / 2)
            return false;
        if(position.x >= MAP_WIDTH || position.y >= MAP_HEIGHT)
            return false;
        return true;
    }

    void draw(coordinate camera)
    {
        if(position.x < camera.x || position.y < camera.y)
            return;
        if(position.x >= camera.x + WINDOW_WIDTH || position.y >= camera.y + WINDOW_HEIGHT)
            return;
        int draw_x = position.x - camera.x;
        int draw_y = position.y - camera.y;
        al_draw_filled_circle(draw_x, draw_y, size / 2, color);
    }

    const void set(int new_x, int new_y, double new_dx, double new_dy)
    {
        position.set(new_x - size / 2, new_y - size / 2);
        dx = new_dx;
        dy = new_dy;
        double dis = sqrt(dx * dx + dy * dy);
        dx *= speed / dis;
        dy *= speed / dis;
    }

    projectile& operator=(projectile & other)
    {
        this->position = other.position;
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
