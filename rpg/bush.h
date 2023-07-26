#ifndef __BUSH_H__
#define __BUSH_H__

#include "plant.h"

class bush : public plant{
public:

    bush(double x, double y, ALLEGRO_BITMAP ** bitmaps)
    {
        bitmap_index = BITMAP_BUSH_INDEX;
        bitmap_on_fire_index = BITMAP_BUSH_ON_FIRE_INDEX;
        time_to_burn = BUSH_TIME_TO_BURN;
        plant::init(x, y, bitmaps);
    }
};

#endif //__BUSH_H__
