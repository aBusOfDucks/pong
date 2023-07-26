#ifndef RPG_PLANT_H
#define RPG_PLANT_H

#include "obstacle.h"

class plant : public obstacle {
protected:
    bool is_on_fire;
    int bitmap_on_fire_index;
    int time_to_burn;

    void init(double x, double y, ALLEGRO_BITMAP ** bitmaps)
    {
        is_destroyed_by_magic = false;
        is_destroyed_by_fire = true;
        can_player_pass = false;
        is_on_fire = false;
        entity::init(x, y, bitmaps);
    }

public:
    void hit_by(int type) override
    {
        if(type == FIRE_TYPE)
        {
            if (is_on_fire)
                kill();
            else
            {
                is_on_fire = true;
                bitmap_index = bitmap_on_fire_index;
            }
        }
    }
    void move(entity ** entities, coordinate player_hitbox_start, coordinate player_hitbox_end)
    {
        if (exist)
        {
            if (time_to_burn <= 0)
                kill();
            if (is_on_fire)
                time_to_burn--;
        }
        obstacle::move(entities, player_hitbox_start, player_hitbox_end);
    }
};

#endif //RPG_PLANT_H
