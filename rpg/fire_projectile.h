#ifndef __FIRE_PROJECTILE_H__
#define __FIRE_PROJECTILE_H__

#include "projectile.h"

class fire_projectile: public projectile {
public:
    fire_projectile(ALLEGRO_BITMAP ** bitmaps)
    {
        dx = 0;
        dy = 0;
        speed = FIRE_PROJECTILE_SPEED;
        range = FIRE_PROJECTILE_RANGE;
        type = FIRE_TYPE;
        bitmap_index = BITMAP_FIRE_PROJECTILE_INDEX;
        width = al_get_bitmap_width(bitmaps[bitmap_index]);
        height = al_get_bitmap_height(bitmaps[bitmap_index]);
    }

    fire_projectile(coordinate camera, int mouse_x, int mouse_y, ALLEGRO_BITMAP ** bitmaps)
    {
        position.x = camera.x + mouse_x;
        position.y = camera.y + mouse_y;
        speed = FIRE_PROJECTILE_SPEED;
        range = FIRE_PROJECTILE_RANGE;
        type = FIRE_TYPE;
        bitmap_index = BITMAP_FIRE_PROJECTILE_INDEX;
        width = al_get_bitmap_width(bitmaps[bitmap_index]);
        height = al_get_bitmap_height(bitmaps[bitmap_index]);
    }

};

#endif //__FIRE_PROJECTILE_H__
