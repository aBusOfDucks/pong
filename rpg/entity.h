#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "coordinate.h"
#include <iostream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

class entity {
protected:
    coordinate position;
    bool is_destroyed_by_magic;
    bool is_destroyed_by_fire;
    bool can_player_pass;

public:
    entity()
    {
        position.set(0, 0);
    }
    void set(double x, double y)
    {
        position.set(x, y);
    }
    virtual void draw(coordinate camera) = 0;
};

#endif //__ENTITY_H__
