#ifndef __PIG_H__
#define __PIG_H__

#include "enemy.h"

class pig : public enemy {
private:
    void eat_berry()
    {
        heal(PIG_BERRIES_HEAL);
    }
public:

    int entity_interaction(int code) override
    {
        if(code == ENTITY_CODE_EAT_BERRIES)
            eat_berry();
        return ENTITY_ANS_NONE;
    }

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
        bool has_berries = false;
        if(e->get_type() == BUSH_TYPE)
        {
            if(e->entity_interaction(ENTITY_CODE_DOES_HAVE_BERRIES) == ENTITY_ANS_HAS_BERRIES)
            {
                has_berries = true;
            }
        }
        bool ans = entity::entity_collide(e);
        if(ans && has_berries)
            eat_berry();
        return ans;
    }
};

#endif //__PIG_H__
