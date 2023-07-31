#ifndef __PIG_H__
#define __PIG_H__

#include "enemy.h"

class pig : public enemy {
public:
    pig(double x, double y, ALLEGRO_BITMAP ** bitmaps)
    {
        bitmap_index = BITMAP_PIG_INDEX;
        max_health = PIG_HEALTH;
        fire_damage = PIG_FIRE_DAMAGE;
        magic_damage = PIG_MAGIC_DAMAGE;
        entity_type = PIG_TYPE;
        enemy::init(x, y, bitmaps);
    }
    bool entity_collide(entity * e) override
    {
        bool ans = entity::entity_collide(e);
        if(ans)
            if(e->get_type() == BUSH_TYPE)
                heal(PIG_BERRIES_HEAL);
        return ans;
    }

    bool collide(coordinate left_upper, coordinate right_bottom, int type) override
    {
        bool ans = entity::collide(left_upper, right_bottom, type);
        if(ans)
            if(type == BUSH_TYPE)
                heal(PIG_BERRIES_HEAL);
        return ans;
    }
};

#endif //__PIG_H__
