#ifndef __TREE_H__
#define __TREE_H__

#include "entity.h"
#include "coordinate.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>

class tree : public entity{
public:

    tree(double x, double y)
    {
        position.set(x, y);
        hitbox_end.set(x + std::max(TREE_TRUNK_WIDTH, TREE_LEAVES_WIDTH), y + TREE_LEAVES_HEIGHT + TREE_TRUNK_HEIGHT);
        is_destroyed_by_magic = false;
        is_destroyed_by_fire = true;
        can_player_pass = false;
    }

    void draw(coordinate camera) override
    {
        if(position.x + std::max(TREE_TRUNK_WIDTH, TREE_LEAVES_WIDTH) < camera.x || position.y + TREE_LEAVES_HEIGHT + TREE_TRUNK_HEIGHT < camera.y)
            return;
        if(position.x >= camera.x + WINDOW_WIDTH || position.y >= camera.y + WINDOW_HEIGHT)
            return;
        int draw_x = position.x - camera.x;
        int draw_y = position.y - camera.y;
        al_draw_filled_rectangle(draw_x, draw_y, draw_x + TREE_LEAVES_WIDTH, draw_y +  TREE_LEAVES_HEIGHT, TREE_LEAVES_COLOR);
        draw_x += (TREE_LEAVES_WIDTH - TREE_TRUNK_WIDTH) / 2;
        draw_y += TREE_LEAVES_HEIGHT;
        al_draw_filled_rectangle(draw_x, draw_y, draw_x + TREE_TRUNK_WIDTH, draw_y +  TREE_TRUNK_HEIGHT, TREE_TRUNK_COLOR);
    }

};

#endif //__TREE_H__
