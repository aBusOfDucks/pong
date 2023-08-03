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
    double dx, dy;
    double speed;
    int chance_to_change_direction;

    void heal(int points)
    {
        health_points += points;
        if(health_points > max_health)
            health_points = max_health;
    }


    void init(double x, double y, ALLEGRO_BITMAP ** bitmaps)
    {
        dx = 0;
        dy = 0;
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
        if(check_ban_map(BITMAP_WATER_MAP_INDEX))
            return false;
        return true;
    }

    void move_in_direction(int dir, entity ** entities, entity * player)
    {
        position.change(dx, dy);
        update_hitbox();
        if(!check_position(entities, player))
        {
            position.change(-dx, -dy);
            update_hitbox();
        }
    }

    void new_direction(int new_dx, int new_dy)
    {
        if(dx == 0 && dy == 0)
        {
            dx = new_dx;
            dy = new_dy;
            double dis = sqrt(dx * dx + dy * dy);
            if(dis > 0)
            {
                dx *= speed / dis;
                dy *= speed / dis;
            }
        }
        else
        {
            dx = 0;
            dy = 0;
        }
    }

public:

    bool check_map_position() override
    {
        if(check_ban_map(BITMAP_WATER_MAP_INDEX))
            return false;

        return entity::check_map_position();
    }

    void hit_by(int type) override
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



    void move(entity ** entities, entity * player) override
    {
        if(!exist)
            return;
        move_in_direction(direction, entities, player);
        std::random_device dev;
        std::mt19937 rng;
        rng = std::mt19937(dev());
        std::uniform_int_distribution<std::mt19937::result_type> change_direction_generator;
        std::uniform_int_distribution<std::mt19937::result_type> new_direction_generator;

        change_direction_generator = std::uniform_int_distribution<std::mt19937::result_type>(0, chance_to_change_direction);
        new_direction_generator = std::uniform_int_distribution<std::mt19937::result_type>(-100, 100);
        if(change_direction_generator(rng) == 0)
        {
            new_direction(new_direction_generator(rng), new_direction_generator(rng));
        }
    }
};

#endif //__ENEMY_H__
