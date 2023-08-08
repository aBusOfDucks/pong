#ifndef RPG_PLANT_H
#define RPG_PLANT_H

#include "obstacle.h"

class plant : public obstacle {
protected:
    bool is_on_fire;
    int bitmap_default;
    int bitmap_on_fire_index;
    int time_to_burn;
    int time_to_burn_default;

    void init(double x, double y, ALLEGRO_BITMAP ** bitmaps)
    {
        is_destroyed_by_magic = false;
        is_destroyed_by_fire = true;
        is_on_fire = false;
        bitmap_default = bitmap_index;
        time_to_burn_default = time_to_burn;
        entity::init(x, y, bitmaps);
    }

public:

    bool check_map_position() override
    {

        if(check_ban_map(BITMAP_PLANT_BAN_MAP_INDEX))
            return false;

        return entity::check_map_position();
    }

    virtual void hit_by(int type) override
    {
        if(type == FIRE_PROJECTILE_TYPE)
        {
            if (is_on_fire)
                kill();
            else
            {
                is_on_fire = true;
                bitmap_index = bitmap_on_fire_index;
            }
        }
        if(type == MAGIC_PROJECTILE_TYPE)
        {
            if(is_on_fire)
            {
                is_on_fire = false;
                bitmap_index = bitmap_default;
                time_to_burn = time_to_burn_default;
            }
        }
        if(type == DEATH_PROJECTILE_TYPE)
        {
            kill();
        }
    }
    void move(entity ** entities, entity * player) override
    {
        if (exist)
        {
            if (time_to_burn <= 0)
                kill();
            if (is_on_fire)
                time_to_burn--;
        }
        obstacle::move(entities, player);
    }
};

#endif //RPG_PLANT_H
