#ifndef __ROCK_H__
#define __ROCK_H__


#include "obstacle.h"

class rock : public obstacle{
public:

    rock(double x, double y, ALLEGRO_BITMAP ** bitmaps)
    {
        bitmap_index = BITMAP_ROCK_INDEX;
        is_destroyed_by_magic = false;
        is_destroyed_by_fire = false;
        can_player_pass = false;
        entity_type = ROCK_TYPE;
        entity::init(x, y, bitmaps);
    }
    bool entity_collide(entity * e)
    {
        bool ans = entity::entity_collide(e);
        if(ans)
            if(e->get_type() == ORC_TYPE)
                kill();
        return ans;
    }

    bool collide(coordinate left_upper, coordinate right_bottom, int type)
    {
        bool ans = entity::collide(left_upper, right_bottom, type);
        if(ans)
            if(type == ORC_TYPE)
                kill();
        return ans;
    }
};

#endif //__ROCK_H__
