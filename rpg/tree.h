#ifndef __TREE_H__
#define __TREE_H__

#include "obstacle.h"

class tree : public obstacle{
public:

    tree(double x, double y, ALLEGRO_BITMAP ** bitmaps)
    {
        bitmap_index = BITMAP_TREE_INDEX;
        is_destroyed_by_magic = false;
        is_destroyed_by_fire = true;
        can_player_pass = false;
        entity::init(x, y, bitmaps);
    }
};

#endif //__TREE_H__
