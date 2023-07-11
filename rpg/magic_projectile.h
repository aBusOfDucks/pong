#ifndef __MAGIC_PROJECTILE_H__
#define __MAGIC_PROJECTILE_H__

#include "const.h"
#include "coordinate.h"
#include <mutex>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "projectile.h"

class magic_projectile: public projectile {
public:
    magic_projectile()
    {
        dx = 0;
        dy = 0;
        color = MAGIC_PROJECTILE_COLOR;
        size = MAGIC_PROJECTILE_SIZE;
        speed = MAGIC_PROJECTILE_SPEED;
        range = MAGIC_PROJECTILE_RANGE;
    }

    magic_projectile(coordinate camera, int mouse_x, int mouse_y)
    {
        x = camera.x * MAP_CELL_SIZE + mouse_x;
        y = camera.y * MAP_CELL_SIZE + mouse_y;
        color = MAGIC_PROJECTILE_COLOR;
        size = MAGIC_PROJECTILE_SIZE;
        speed = MAGIC_PROJECTILE_SPEED;
        range = MAGIC_PROJECTILE_RANGE;
    }

};

#endif //__MAGIC_PROJECTILE_H__
