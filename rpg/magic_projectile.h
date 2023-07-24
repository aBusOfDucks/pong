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
        speed = MAGIC_PROJECTILE_SPEED;
        range = MAGIC_PROJECTILE_RANGE;
        type = MAGIC_TYPE;
        bitmap = al_load_bitmap(MAGIC_PROJECTILE_PATH);
        width = al_get_bitmap_width(bitmap);
        height = al_get_bitmap_height(bitmap);
    }

    magic_projectile(coordinate camera, int mouse_x, int mouse_y)
    {
        position.x = camera.x + mouse_x;
        position.y = camera.y + mouse_y;
        speed = MAGIC_PROJECTILE_SPEED;
        range = MAGIC_PROJECTILE_RANGE;
        type = MAGIC_TYPE;
        bitmap = al_load_bitmap(MAGIC_PROJECTILE_PATH);
        width = al_get_bitmap_width(bitmap);
        height = al_get_bitmap_height(bitmap);
    }

};

#endif //__MAGIC_PROJECTILE_H__
