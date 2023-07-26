#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "coordinate.h"
#include "const.h"
#include <iostream>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include "bitmaps.h"

class entity {
protected:
    coordinate position;
    bool can_player_pass;
    coordinate hitbox_end;
    coordinate hitbox_start;
    bool exist = true;
    int bitmap_index;
    int width, height;
    void init(double x, double y, ALLEGRO_BITMAP ** bitmaps)
    {
        position.set(x, y);
        width = al_get_bitmap_width(bitmaps[bitmap_index]);
        height = al_get_bitmap_height(bitmaps[bitmap_index]);
        hitbox_start.set(x, y);
        hitbox_end.set(x + width, y + height);
    }

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
    void draw(coordinate camera, ALLEGRO_BITMAP ** bitmaps)
    {
        if(!exist)
            return;
        if(position.x + width < camera.x || position.y + height < camera.y)
            return;
        if(position.x >= camera.x + WINDOW_WIDTH || position.y >= camera.y + WINDOW_HEIGHT)
            return;

        int draw_x = position.x - camera.x;
        int draw_y = position.y - camera.y;
        al_draw_bitmap(bitmaps[bitmap_index], draw_x, draw_y, 0);
    }

    bool entity_collide(entity * e)
    {
        return e->collide(hitbox_start, hitbox_end);
    }

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
    bool check_map_position()
    {
        if(position.x < 0 || position.y < 0)
            return false;
        if(position.x + width >= MAP_WIDTH || position.y + height >= MAP_HEIGHT)
            return false;
        return true;
    }
    virtual void hit_by(int type) = 0;
    virtual void move(entity ** entities, coordinate player_hitbox_start, coordinate player_hitbox_end) = 0;
};

#endif //__ENTITY_H__
