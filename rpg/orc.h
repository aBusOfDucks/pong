#ifndef __ORC_H__
#define __ORC_H__

#include "enemy.h"

class orc : public enemy {
public:

    bool check_map_position()
    {
        if(check_ban_map(BITMAP_ORC_BAN_MAP_INDEX))
            return false;

        return entity::check_map_position();
    }

    orc(double x, double y, ALLEGRO_BITMAP ** bitmaps)
    {
        bitmap_index = BITMAP_ORC_INDEX;
        max_health = ORC_HEALTH;
        fire_damage = ORC_FIRE_DAMAGE;
        magic_damage = ORC_MAGIC_DAMAGE;
        entity_type = ORC_TYPE;
        speed = ORC_SPEED;
        chance_to_change_direction = ORC_CHANCE_TO_CHANGE_DIRECTION;
        enemy::init(x, y, bitmaps);
    }
};

#endif //__ORC_H__

