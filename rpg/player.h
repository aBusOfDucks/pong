#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <mutex>
#include <thread>
#include <condition_variable>
#include <random>
#include <queue>
#include "entity.h"
#include "enemy.h"

class player : public entity{
protected:

    int direction_x;
    int direction_y;

    void teleport(int x, int y)
    {
        position.set(x, y);
    }

public:

    player(ALLEGRO_BITMAP ** bitmaps)
    {
        direction_x = 0;
        direction_y = 0;
        bitmap_index = BITMAP_PLAYER_INDEX;
        entity_type = PLAYER_TYPE;
        entity::init(0, 0, bitmaps);
    }

    void move(entity ** entities, entity * player)
    {
        position.change(direction_x, direction_y);
        update_hitbox();
        for(int i = 0; i < MAX_ENTITIES; i++)
        {
            if(entity_collide(entities[i]))
            {
                position.change(-direction_x, -direction_y);
                i = MAX_ENTITIES;
            }
        }
        position.trim(map_width - width, map_height - height);
        position.trim_bottom(0, 0);
        update_hitbox();
    }

    void change_direction(int dx, int dy)
    {
        direction_x += dx;
        direction_y += dy;
        if(direction_x > 1)
            direction_x = 1;
        if(direction_x < -1)
            direction_x = -1;
        if(direction_y > 1)
            direction_y = 1;
        if(direction_y < -1)
            direction_y = -1;
    }

    bool entity_collide(entity * e)
    {
        bool ans = entity::entity_collide(e);
        if (ans)
        {
            if (e->get_type() == ORC_TYPE)
                teleport(0, 0);
        }
        return ans;
    }

    bool collide(coordinate left_upper, coordinate right_bottom, int type)
    {
        bool ans = entity::collide(left_upper, right_bottom, type);
        if (ans)
        {
            if (type == ORC_TYPE)
                teleport(0, 0);
        }
        return ans;
    }

    coordinate get_position()
    {
        return position;
    }

    void hit_by(int type)
    {
        return;
    }
};

#endif /* __PLAYER_H__ */