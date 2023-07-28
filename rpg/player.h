#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <mutex>
#include <thread>
#include <condition_variable>
#include <random>
#include <queue>
#include "entity.h"

class player{
private:

    std::mutex mutex_position;
    coordinate position;
    int direction_x;
    int direction_y;
    int width, height;
    int map_width, map_height;

public:

    player(ALLEGRO_BITMAP ** bitmaps)
    {
        direction_x = 0;
        direction_y = 0;
        position.set(0, 0);
        width = al_get_bitmap_width(bitmaps[BITMAP_PLAYER_INDEX]);
        height = al_get_bitmap_height(bitmaps[BITMAP_PLAYER_INDEX]);
        map_width = al_get_bitmap_width(bitmaps[BITMAP_MAP_INDEX]);
        map_height = al_get_bitmap_height(bitmaps[BITMAP_MAP_INDEX]);
    }
    void move(entity ** entities)
    {
        std::unique_lock<std::mutex> lock(mutex_position);
        position.change(direction_x, direction_y);
        coordinate hitbox_start(position.x, position.y);
        coordinate hitbox_end(position.x + width, position.y + height);
        for(int i = 0; i < MAX_ENTITIES; i++)
        {
            if(entities[i]->collide(hitbox_start, hitbox_end, PLAYER_TYPE))
            {
                position.change(-direction_x, -direction_y);
                i = MAX_ENTITIES;
            }
        }
        position.trim(map_width - width, map_height - height);
        position.trim_bottom(0, 0);
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
        std::unique_lock<std::mutex> lock(mutex_position);
        return position;
    }

    coordinate get_hitbox_end()
    {
        std::unique_lock<std::mutex> lock(mutex_position);
        coordinate hitbox_end(position.x + width, position.y + height);
        return hitbox_end;
    }

    coordinate get_position()
    {
        std::unique_lock<std::mutex> lock(mutex_position);
        return position;
    }

    void draw(coordinate camera, ALLEGRO_BITMAP ** bitmaps)
    {
        if(position.x < camera.x || position.y < camera.y)
            return;
        if(position.x >= camera.x + WINDOW_WIDTH || position.y >= camera.y + WINDOW_HEIGHT)
            return;
        int draw_x = position.x - camera.x;
        int draw_y = position.y - camera.y;
        al_draw_bitmap(bitmaps[BITMAP_PLAYER_INDEX], draw_x, draw_y, 0);
    }

};

#endif /* __PLAYER_H__ */