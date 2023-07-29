#ifndef __PIG_H__
#define __PIG_H__

#include "enemy.h"

class pig : public enemy {
public:
    pig(double x, double y, ALLEGRO_BITMAP ** bitmaps)
    {
        bitmap_index = BITMAP_PIG_INDEX;
        health_points = PIG_HEALTH;
        fire_damage = PIG_FIRE_DAMAGE;
        magic_damage = PIG_MAGIC_DAMAGE;
        entity_type = PIG_TYPE;
        entity::init(x, y, bitmaps);
    }
};

#endif //__PIG_H__
