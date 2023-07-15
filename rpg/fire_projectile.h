#ifndef __FIRE_PROJECTILE_H__
#define __FIRE_PROJECTILE_H__

#include "const.h"
#include "coordinate.h"
#include <mutex>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "projectile.h"

class fire_projectile: public projectile {
public:
    fire_projectile()
    {
        dx = 0;
        dy = 0;
        color = FIRE_PROJECTILE_COLOR;
        size = FIRE_PROJECTILE_SIZE;
        speed = FIRE_PROJECTILE_SPEED;
        range = FIRE_PROJECTILE_RANGE;
        type = FIRE_TYPE;
    }

    fire_projectile(coordinate camera, int mouse_x, int mouse_y)
    {
        x = camera.x + mouse_x;
        y = camera.y + mouse_y;
        color = FIRE_PROJECTILE_COLOR;
        size = FIRE_PROJECTILE_SIZE;
        speed = FIRE_PROJECTILE_SPEED;
        range = FIRE_PROJECTILE_RANGE;
        type = FIRE_TYPE;
    }

};

#endif //__FIRE_PROJECTILE_H__
