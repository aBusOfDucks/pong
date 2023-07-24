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
        speed = FIRE_PROJECTILE_SPEED;
        range = FIRE_PROJECTILE_RANGE;
        type = FIRE_TYPE;
        bitmap = al_load_bitmap(FIRE_PROJECTILE_PATH);
        width = al_get_bitmap_width(bitmap);
        height = al_get_bitmap_height(bitmap);
    }

    fire_projectile(coordinate camera, int mouse_x, int mouse_y)
    {
        position.x = camera.x + mouse_x;
        position.y = camera.y + mouse_y;
        speed = FIRE_PROJECTILE_SPEED;
        range = FIRE_PROJECTILE_RANGE;
        type = FIRE_TYPE;
        bitmap = al_load_bitmap(FIRE_PROJECTILE_PATH);
        width = al_get_bitmap_width(bitmap);
        height = al_get_bitmap_height(bitmap);
    }

};

#endif //__FIRE_PROJECTILE_H__
