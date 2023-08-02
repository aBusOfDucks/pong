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
    coordinate hitbox_end;
    coordinate hitbox_start;
    bool exist;
    int bitmap_index;
    int width, height;
    int entity_type;
    int map_width, map_height;
    ALLEGRO_BITMAP ** bitmaps;

    void init(double x, double y, ALLEGRO_BITMAP ** bitmaps)
    {
        exist = true;
        position.set(x, y);
        width = al_get_bitmap_width(bitmaps[bitmap_index]);
        height = al_get_bitmap_height(bitmaps[bitmap_index]);
        hitbox_start.set(x, y);
        hitbox_end.set(x + width, y + height);
        map_width = al_get_bitmap_width(bitmaps[BITMAP_MAP_INDEX]);
        map_height = al_get_bitmap_height(bitmaps[BITMAP_MAP_INDEX]);
        this->bitmaps = bitmaps;
    }
    void update_hitbox()
    {
        hitbox_start.set(position.x, position.y);
        hitbox_end.set(position.x + width, position.y + height);
    }

    bool check_ban_map(int index)
    {
        if(check_ban(bitmaps, index, hitbox_start.x, hitbox_start.y))
            return true;
        if(check_ban(bitmaps, index, hitbox_start.x, hitbox_end.y))
            return true;
        if(check_ban(bitmaps, index, hitbox_end.x, hitbox_start.y))
            return true;
        if(check_ban(bitmaps, index, hitbox_end.x, hitbox_end.y))
            return true;
        return false;
    }

public:

    virtual int entity_interaction(int code)
    {
        return ENTITY_ANS_NONE;
    }

    int get_type()
    {
        return entity_type;
    }

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

    virtual bool entity_collide(entity * e)
    {
        if(!exist)
            return false;
        return e->collide(hitbox_start, hitbox_end, entity_type);
    }

    virtual bool collide(coordinate left_upper, coordinate right_bottom, int type)
    {
        if(!exist)
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

    coordinate get_hitbox_start()
    {
        return position;
    }

    coordinate get_hitbox_end()
    {
        coordinate hitbox_end(position.x + width, position.y + height);
        return hitbox_end;
    }

    virtual bool check_map_position()
    {
        if(position.x < 0 || position.y < 0)
            return false;
        if(position.x + width >= map_width || position.y + height >= map_height)
            return false;

        if(check_ban_map(BITMAP_ENTITY_BAN_MAP_INDEX))
            return false;

        return true;
    }
    virtual void hit_by(int type) = 0;
    virtual void move(entity ** entities, entity * player) = 0;
};

#endif //__ENTITY_H__
