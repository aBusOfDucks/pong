#ifndef __DEATH_PROJECTILE_H__
#define __DEATH_PROJECTILE_H__
#include "projectile.h"

class death_projectile: public projectile {
public:
    death_projectile(ALLEGRO_BITMAP ** bitmaps)
    {
        dx = 0;
        dy = 0;
        speed = DEATH_PROJECTILE_SPEED;
        range = DEATH_PROJECTILE_RANGE;
        type = DEATH_PROJECTILE_TYPE;
        bitmap_index = BITMAP_DEATH_PROJECTILE_INDEX;
        destroy_on_hit = false;
        projectile::init(bitmaps);
    }

    death_projectile(coordinate camera, int mouse_x, int mouse_y, ALLEGRO_BITMAP ** bitmaps)
    {
        position.x = camera.x + mouse_x;
        position.y = camera.y + mouse_y;
        speed = DEATH_PROJECTILE_SPEED;
        range = DEATH_PROJECTILE_RANGE;
        type = DEATH_PROJECTILE_TYPE;
        bitmap_index = BITMAP_DEATH_PROJECTILE_INDEX;
        destroy_on_hit = false;
        projectile::init(bitmaps);
    }

    death_projectile(int x, int y, int dx, int dy, ALLEGRO_BITMAP ** bitmaps)
    {
        speed = DEATH_PROJECTILE_SPEED;
        range = DEATH_PROJECTILE_RANGE;
        type = DEATH_PROJECTILE_TYPE;
        bitmap_index = BITMAP_DEATH_PROJECTILE_INDEX;
        destroy_on_hit = false;
        set(x, y, dx, dy);
        projectile::init(bitmaps);
    }
};
#endif //__DEATH_PROJECTILE_H__
