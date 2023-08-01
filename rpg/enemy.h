#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "entity.h"
#include <random>

class enemy : public entity {
protected:
    int health_points;
    int max_health;
    int fire_damage;
    int magic_damage;
    ALLEGRO_COLOR color;
    int direction = NONE;

    void heal(int points)
    {
        health_points += points;
        if(health_points > max_health)
            health_points = max_health;
    }

    void init(double x, double y, ALLEGRO_BITMAP ** bitmaps)
    {
        health_points = max_health;
        entity::init(x, y, bitmaps);
    }
    bool check_position(entity ** entities, entity * player)
    {
        int number_of_collisions = 0;
        if(position.x < 0 || position.y < 0)
            return false;
        if(position.x + width >= map_width || position.y + height >= map_height)
            return false;
        for(int i = 0; i < MAX_ENTITIES; i++)
        {
            if(entity_collide(entities[i]))
                number_of_collisions++;
        }
        if(number_of_collisions > 1)
            return false;
        if(entity_collide(player))
            return false;
        return true;
    }

    void move_in_direction(int dir, entity ** entities, entity * player)
    {
        if(dir == UP)
            position.y--;
        if(dir == DOWN)
            position.y++;
        if(dir == LEFT)
            position.x--;
        if(dir == RIGHT)
            position.x++;
        update_hitbox();
        if(!check_position(entities, player))
        {
            if(dir == UP)
                position.y++;
            if(dir == DOWN)
                position.y--;
            if(dir == LEFT)
                position.x++;
            if(dir == RIGHT)
                position.x--;
            update_hitbox();
        }
    }
public:
    void hit_by(int type)
    {
        if(type == FIRE_PROJECTILE_TYPE)
        {
            health_points -= fire_damage;
        }
        if(type == MAGIC_PROJECTILE_TYPE)
        {
            health_points -= magic_damage;
        }
        if(health_points <= 0)
            kill();
    }
    void move(entity ** entities, entity * player)
    {
        if(!exist)
            return;
        move_in_direction(direction, entities, player);
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

#endif //__ENEMY_H__
