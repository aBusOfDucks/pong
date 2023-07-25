#ifndef __TREE_H__
#define __TREE_H__

#include "entity.h"
#include "coordinate.h"
#include "obstacle.h"

class tree : public obstacle{
public:

    tree(double x, double y, ALLEGRO_BITMAP ** bitmaps)
    {
        position.set(x, y);
        hitbox_start.set(x, y);
        bitmap_index = BITMAP_TREE_INDEX;
        width = al_get_bitmap_width(bitmaps[bitmap_index]);
        height = al_get_bitmap_height(bitmaps[bitmap_index]);
        hitbox_end.set(x + width, y + height);
        is_destroyed_by_magic = false;
        is_destroyed_by_fire = true;
        can_player_pass = false;
    }
};

#endif //__TREE_H__
