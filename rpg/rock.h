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
        entity::init(x, y, bitmaps);
    }
};

#endif //__ROCK_H__
