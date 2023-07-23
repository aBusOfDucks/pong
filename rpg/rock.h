#ifndef __ROCK_H__
#define __ROCK_H__

#include "entity.h"
#include "coordinate.h"
#include "obstacle.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>

class rock : public obstacle{
public:

    rock(double x, double y)
    {
        position.set(x, y);
        bitmap = al_load_bitmap(ROCK_1_PATH);
        width = al_get_bitmap_width(bitmap);
        height = al_get_bitmap_height(bitmap);
        hitbox_start.set(x, y);
        hitbox_end.set(x + width, y + height);
        is_destroyed_by_magic = false;
        is_destroyed_by_fire = false;
        can_player_pass = false;
    }
};

#endif //__ROCK_H__
