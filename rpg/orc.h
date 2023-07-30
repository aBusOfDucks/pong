#ifndef __ORC_H__
#define __ORC_H__

#include "enemy.h"

class orc : public enemy {
public:

    bool check_map_position(ALLEGRO_BITMAP ** bitmaps)
    {
        if(check_ban(bitmaps, BITMAP_ORC_BAN_MAP_INDEX, hitbox_start.x, hitbox_start.y))
            return false;
        if(check_ban(bitmaps, BITMAP_ORC_BAN_MAP_INDEX, hitbox_start.x, hitbox_end.y))
            return false;
        if(check_ban(bitmaps, BITMAP_ORC_BAN_MAP_INDEX, hitbox_end.x, hitbox_start.y))
            return false;
        if(check_ban(bitmaps, BITMAP_ORC_BAN_MAP_INDEX, hitbox_end.x, hitbox_end.y))
            return false;

        return entity::check_map_position(bitmaps);
    }

    orc(double x, double y, ALLEGRO_BITMAP ** bitmaps)
    {
        bitmap_index = BITMAP_ORC_INDEX;
        health_points = ORC_HEALTH;
        fire_damage = ORC_FIRE_DAMAGE;
        magic_damage = ORC_MAGIC_DAMAGE;
        entity_type = ORC_TYPE;
        entity::init(x, y, bitmaps);
    }
    void move(entity ** entities, entity * player)
    {
        if(!exist)
            return;
        if(direction == ORC_DIRECTION_UP_RIGHT)
        {
            move_in_direction(UP, entities, player);
            move_in_direction(RIGHT, entities, player);
        }
        if(direction == ORC_DIRECTION_DOWN_LEFT)
        {
            move_in_direction(DOWN, entities, player);
            move_in_direction(LEFT, entities, player);
        }
        if(direction == ORC_DIRECTION_UP_LEFT)
        {
            move_in_direction(UP, entities, player);
            move_in_direction(LEFT, entities, player);
        }
        if(direction == ORC_DIRECTION_DOWN_RIGHT)
        {
            move_in_direction(DOWN, entities, player);
            move_in_direction(RIGHT, entities, player);
        }
        std::random_device dev;
        std::mt19937 rng;
        rng = std::mt19937(dev());
        std::uniform_int_distribution<std::mt19937::result_type> change_direction_generator;

        change_direction_generator = std::uniform_int_distribution<std::mt19937::result_type>(0, CHANCE_TO_CHANGE_DIRECTION);
        if(change_direction_generator(rng) == 0)
        {
            if(direction == NONE)
            {
                std::uniform_int_distribution <std::mt19937::result_type> new_direction;
                new_direction = std::uniform_int_distribution<std::mt19937::result_type>(0, DIRECTIONS_NUMBER);
                direction = new_direction(rng);
            }
            else
                direction = NONE;
        }
    }
};

#endif //__ORC_H__

