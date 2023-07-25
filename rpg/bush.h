#ifndef __BUSH_H__
#define __BUSH_H__

#include "obstacle.h"

class bush : public obstacle{
public:

    bush(double x, double y, ALLEGRO_BITMAP ** bitmaps)
    {
        bitmap_index = BITMAP_BUSH_INDEX;
        is_destroyed_by_magic = false;
        is_destroyed_by_fire = true;
        can_player_pass = false;
        entity::init(x, y, bitmaps);
    }
};

#endif //__BUSH_H__
