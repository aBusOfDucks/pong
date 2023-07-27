#ifndef __TREE_H__
#define __TREE_H__

#include "plant.h"

class tree : public plant{
public:

    tree(double x, double y, ALLEGRO_BITMAP ** bitmaps)
    {
        bitmap_index = BITMAP_TREE_INDEX;
        bitmap_on_fire_index = BITMAP_TREE_ON_FIRE_INDEX;
        time_to_burn = TREE_TIME_TO_BURN;
        entity_type = TREE_TYPE;
        plant::init(x, y, bitmaps);
    }
};

#endif //__TREE_H__
