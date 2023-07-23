#ifndef __PIG_H__
#define __PIG_H__

#include "enemy.h"
#include "const.h"

class pig : public enemy {
public:
    pig(double x, double y)
    {
        position.set(x, y);
        bitmap = al_load_bitmap(PIG_1_PATH);
        width = al_get_bitmap_width(bitmap);
        height = al_get_bitmap_height(bitmap);
        hitbox_start.set(x, y);
        hitbox_end.set(x + width, y + height);
        health_points = PIG_HEALTH;
        fire_damage = PIG_FIRE_DAMAGE;
        magic_damage = PIG_MAGIC_DAMAGE;
        can_player_pass = false;
    }
};

#endif //__PIG_H__
