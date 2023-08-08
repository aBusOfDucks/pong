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
        type = FIRE_PROJECTILE_TYPE;
        bitmap_index = BITMAP_FIRE_PROJECTILE_INDEX;
        destroy_on_hit = true;
        projectile::init(bitmaps);
    }

    fire_projectile(coordinate camera, int mouse_x, int mouse_y, ALLEGRO_BITMAP ** bitmaps)
    {
        position.x = camera.x + mouse_x;
        position.y = camera.y + mouse_y;
        speed = FIRE_PROJECTILE_SPEED;
        range = FIRE_PROJECTILE_RANGE;
        type = FIRE_PROJECTILE_TYPE;
        bitmap_index = BITMAP_FIRE_PROJECTILE_INDEX;
        destroy_on_hit = true;
        projectile::init(bitmaps);
    }

    fire_projectile(int x, int y, int dx, int dy, ALLEGRO_BITMAP ** bitmaps)
    {
        speed = FIRE_PROJECTILE_SPEED;
        range = FIRE_PROJECTILE_RANGE;
        type = FIRE_PROJECTILE_TYPE;
        bitmap_index = BITMAP_FIRE_PROJECTILE_INDEX;
        destroy_on_hit = true;
        set(x, y, dx, dy);
        projectile::init(bitmaps);

    }

};

#endif //__FIRE_PROJECTILE_H__
