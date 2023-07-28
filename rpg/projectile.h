#ifndef __PROJECTILE_H__
#define __PROJECTILE_H__

#include <mutex>
#include <cmath>
#include "entity.h"

class projectile{
protected:

    std::mutex mutex_position;
    coordinate position;
    double dx, dy;
    double speed;
    int range;
    int type;
    int width, height;
    int bitmap_index;
    int map_width, map_height;

    void init(ALLEGRO_BITMAP ** bitmaps)
    {
        map_width = al_get_bitmap_width(bitmaps[BITMAP_MAP_INDEX]);
        map_height = al_get_bitmap_height(bitmaps[BITMAP_MAP_INDEX]);
        width = al_get_bitmap_width(bitmaps[bitmap_index]);
        height = al_get_bitmap_height(bitmaps[bitmap_index]);
    }

public:

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
        coordinate hitbox_start(position.x, position.y);
        coordinate hitbox_end(position.x + width, position.y + height);
        for(int i = 0; i < MAX_ENTITIES; i++)
        {
            if(entities[i]->collide(hitbox_start, hitbox_end, type))
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
        if(position.x < 0 || position.y < 0)
            return false;
        if(position.x >= map_width || position.y >= map_height)
            return false;
        return true;
    }

    void draw(coordinate camera, ALLEGRO_BITMAP ** bitmaps)
    {
        if(position.x < camera.x || position.y < camera.y)
            return;
        if(position.x >= camera.x + WINDOW_WIDTH || position.y >= camera.y + WINDOW_HEIGHT)
            return;
        int draw_x = position.x - camera.x;
        int draw_y = position.y - camera.y;
        al_draw_bitmap(bitmaps[bitmap_index], draw_x, draw_y, 0);
    }

    const void set(int new_x, int new_y, double new_dx, double new_dy)
    {
        position.set(new_x, new_y);
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
        this->speed = other.speed;
        this->range = other.range;
        this->type = other.type;
        this->width = other.width;
        this->height = other.height;
        this->bitmap_index = other.bitmap_index;
        this->map_width = other.map_width;
        this->map_height = other.map_height;
        return *this;
    }

    void destroy()
    {
        range = 0;
    }
};

#endif //__PROJECTILE_H__
