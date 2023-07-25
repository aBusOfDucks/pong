#ifndef __PIG_H__
#define __PIG_H__

#include "enemy.h"
#include "const.h"

class pig : public enemy {
public:
    pig(double x, double y, ALLEGRO_BITMAP ** bitmaps)
    {
        position.set(x, y);
        bitmap_index = BITMAP_PIG_INDEX;
        width = al_get_bitmap_width(bitmaps[bitmap_index]);
        height = al_get_bitmap_height(bitmaps[bitmap_index]);
        hitbox_start.set(x, y);
        hitbox_end.set(x + width, y + height);
        health_points = PIG_HEALTH;
        fire_damage = PIG_FIRE_DAMAGE;
        magic_damage = PIG_MAGIC_DAMAGE;
        can_player_pass = false;
    }
};

#endif //__PIG_H__
