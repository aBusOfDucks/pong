#ifndef __MAGIC_PROJECTILE_H__
#define __MAGIC_PROJECTILE_H__

#include "projectile.h"

class magic_projectile: public projectile {
public:
    magic_projectile(ALLEGRO_BITMAP ** bitmaps)
    {
        dx = 0;
        dy = 0;
        speed = MAGIC_PROJECTILE_SPEED;
        range = MAGIC_PROJECTILE_RANGE;
        type = MAGIC_PROJECTILE_TYPE;
        bitmap_index = BITMAP_MAGIC_PROJECTILE_INDEX;
        width = al_get_bitmap_width(bitmaps[bitmap_index]);
        height = al_get_bitmap_height(bitmaps[bitmap_index]);
    }

    magic_projectile(coordinate camera, int mouse_x, int mouse_y, ALLEGRO_BITMAP ** bitmaps)
    {
        position.x = camera.x + mouse_x;
        position.y = camera.y + mouse_y;
        speed = MAGIC_PROJECTILE_SPEED;
        range = MAGIC_PROJECTILE_RANGE;
        type = MAGIC_PROJECTILE_TYPE;
        bitmap_index = BITMAP_MAGIC_PROJECTILE_INDEX;
        width = al_get_bitmap_width(bitmaps[bitmap_index]);
        height = al_get_bitmap_height(bitmaps[bitmap_index]);
    }

};

#endif //__MAGIC_PROJECTILE_H__
