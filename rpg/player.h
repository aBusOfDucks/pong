#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <random>
#include <iostream>
#include <queue>
#include "const.h"
#include "coordinate.h"
#include "entity.h"

class player{
private:

    std::mutex mutex_position;
    coordinate position;
    int direction_x;
    int direction_y;

public:

    player()
    {
        direction_x = 0;
        direction_y = 0;
        position.set(PLAYER_SIZE / 2, PLAYER_SIZE / 2);
    }
    void move(entity ** entities)
    {
        std::unique_lock<std::mutex> lock(mutex_position);
        position.change(direction_x, direction_y);
        coordinate hitbox_start(position.x - PLAYER_SIZE / 2, position.y - PLAYER_SIZE / 2);
        coordinate hitbox_end(position.x + PLAYER_SIZE / 2, position.y + PLAYER_SIZE / 2);
        for(int i = 0; i < MAX_ENTITIES; i++)
        {
            if(entities[i]->collide(hitbox_start, hitbox_end))
            {
                position.change(-direction_x, -direction_y);
                i = MAX_ENTITIES;
            }
        }
        position.trim(MAP_WIDTH - PLAYER_SIZE / 2, MAP_HEIGHT - PLAYER_SIZE / 2);
        position.trim_bottom(PLAYER_SIZE / 2, PLAYER_SIZE / 2);
    }

    void change_direction(int dx, int dy)
    {
        std::unique_lock<std::mutex> lock(mutex_position);
        direction_x += dx;
        direction_y += dy;
        if(direction_x > 1)
            direction_x = 1;
        if(direction_x < -1)
            direction_x = -1;
        if(direction_y > 1)
            direction_y = 1;
        if(direction_y < -1)
            direction_y = -1;
    }

    coordinate get_hitbox_start()
    {
        coordinate hitbox_start(position.x - PLAYER_SIZE / 2, position.y - PLAYER_SIZE / 2);
        return hitbox_start;
    }

    coordinate get_hitbox_end()
    {
        coordinate hitbox_end(position.x + PLAYER_SIZE / 2, position.y + PLAYER_SIZE / 2);
        return hitbox_end;
    }

    coordinate get_position()
    {
        std::unique_lock<std::mutex> lock(mutex_position);
        return position;
    }

    void draw(coordinate camera)
    {
        if(position.x < camera.x || position.y < camera.y)
            return;
        if(position.x >= camera.x + WINDOW_WIDTH || position.y >= camera.y + WINDOW_HEIGHT)
            return;
        int draw_x = position.x - camera.x;
        int draw_y = position.y - camera.y;
        al_draw_filled_circle(draw_x, draw_y, PLAYER_SIZE / 2, PLAYER_COLOR);
    }

};

#endif /* __PLAYER_H__ */