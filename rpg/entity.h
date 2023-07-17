#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "coordinate.h"
#include <iostream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

class entity {
protected:
    coordinate position;
    bool can_player_pass;
    coordinate hitbox_end;
    coordinate hitbox_start;
    bool exist = true;


public:
    entity()
    {
        position.set(0, 0);
        hitbox_end.set(-1, -1);
    }
    void set(double x, double y)
    {
        position.set(x, y);
    }
    virtual void draw(coordinate camera) = 0;
    bool collide(coordinate left_upper, coordinate right_bottom)
    {
        if(!exist || can_player_pass)
            return false;
        coordinate left_bottom(left_upper.x, right_bottom.y);
        coordinate right_upper(right_bottom.x, left_upper.y);

        if(left_upper.in_square(hitbox_start, hitbox_end))
            return true;
        if(right_bottom.in_square(hitbox_start, hitbox_end))
            return true;
        if(right_upper.in_square(hitbox_start, hitbox_end))
            return true;
        if(left_bottom.in_square(hitbox_start, hitbox_end))
            return true;

        coordinate hitbox_left_bottom(hitbox_start.x, hitbox_end.y);
        coordinate hitbox_right_upper(hitbox_end.x, hitbox_start.y);
        if(position.in_square(left_upper, right_bottom))
            return true;
        if(hitbox_end.in_square(left_upper, right_bottom))
            return true;
        if(hitbox_left_bottom.in_square(left_upper, right_bottom))
            return true;
        if(hitbox_right_upper.in_square(left_upper, right_bottom))
            return true;

        return false;
    }
    void kill()
    {
        exist = false;
    }
    virtual void hit_by(int type) = 0;
};

#endif //__ENTITY_H__
