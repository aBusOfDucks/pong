#ifndef __PROJECTILE_H__
#define __PROJECTILE_H__

#include "const.h"
#include "coordinate.h"
#include <mutex>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

class projectile{
public:

    std::mutex mutex_position;
    coordinate position;
    int dx, dy;

    projectile()
    {
        dx = 0;
        dy = 0;
    }

    projectile(coordinate camera, int x, int y)
    {
        position = camera;
        position.scale(MAP_CELL_SIZE);
        position.change(x, y);
    }

    void move()
    {
        std::unique_lock<std::mutex> lock(mutex_position);
        position.change(dx, dy);
    }

    bool check()
    {
        if(position.x < 0 || position.y < 0)
            return false;
        if(position.x >= MAP_WIDTH * MAP_CELL_SIZE || position.y >= MAP_HEIGHT * MAP_CELL_SIZE)
            return false;
        return true;
    }

    void draw(coordinate camera)
    {
        camera.scale(MAP_CELL_SIZE);
        if(position.x < camera.x || position.y < camera.y)
            return;
        if(position.x >= camera.x + WINDOW_WIDTH || position.y >= camera.y + WINDOW_HEIGHT)
            return;
        int draw_x = position.x - camera.x;
        int draw_y = position.y - camera.y;
        al_draw_filled_rectangle(draw_x, draw_y, draw_x + PROJECTILE_SIZE, draw_y +  PROJECTILE_SIZE, PROJECTILE_COLOR);
    }

    const void set(int x, int y, int new_dx, int new_dy)
    {
        position.set(x, y);
        dx = new_dx;
        dy = new_dy;
    }
};

#endif //__PROJECTILE_H__
