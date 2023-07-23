#ifndef __BUSH_H__
#define __BUSH_H__

#include "entity.h"
#include "coordinate.h"
#include "obstacle.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <math.h>

class bush : public obstacle{
public:

    bush(double x, double y)
    {
        position.set(x, y);
        bitmap = al_load_bitmap(BUSH_1_PATH);
        width = al_get_bitmap_width(bitmap);
        height = al_get_bitmap_height(bitmap);
        hitbox_start.set(x, y);
        hitbox_end.set(x + width, y + height);
        is_destroyed_by_magic = false;
        is_destroyed_by_fire = true;
        can_player_pass = false;
    }
};

#endif //__BUSH_H__
