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
        type = MAGIC_TYPE;
    }

    magic_projectile(coordinate camera, int mouse_x, int mouse_y)
    {
        position.x = camera.x + mouse_x - MAGIC_PROJECTILE_SIZE / 2;
        position.y = camera.y + mouse_y - MAGIC_PROJECTILE_SIZE / 2;
        color = MAGIC_PROJECTILE_COLOR;
        size = MAGIC_PROJECTILE_SIZE;
        speed = MAGIC_PROJECTILE_SPEED;
        range = MAGIC_PROJECTILE_RANGE;
        type = MAGIC_TYPE;
    }

};

#endif //__MAGIC_PROJECTILE_H__
