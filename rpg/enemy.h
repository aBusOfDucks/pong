#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "entity.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <random>

class enemy : public entity {
protected:
    int health_points;
    int fire_damage;
    int magic_damage;
    int size;
    ALLEGRO_COLOR color;
    int direction = NONE;
    bool check_position(entity ** entities, coordinate player_hitbox_start, coordinate player_hitbox_end)
    {
        int number_of_collisions = 0;
        if(position.x < size / 2 || position.y < size / 2)
            return false;
        if(position.x + size / 2 > MAP_WIDTH || position.y + size / 2 > MAP_HEIGHT)
            return false;
        for(int i = 0; i < MAX_ENTITIES; i++)
        {
            if(entities[i]->collide(hitbox_start, hitbox_end))
                number_of_collisions++;
        }
        if(number_of_collisions > 1)
            return false;
        if(collide(player_hitbox_start, player_hitbox_end))
            return false;
        return true;
    }
    void move_in_direction(int dir, entity ** entities, coordinate player_hitbox_start, coordinate player_hitbox_end)
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
        if(!check_position(entities, player_hitbox_start, player_hitbox_end))
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
        if(type == FIRE_TYPE)
        {
            health_points -= fire_damage;
        }
        if(type == MAGIC_TYPE)
        {
            health_points -= magic_damage;
        }
        if(health_points <= 0)
            kill();
    }
    void draw(coordinate camera)
    {
        if(!exist)
            return;
        if(position.x < camera.x || position.y < camera.y)
            return;
        if(position.x >= camera.x + WINDOW_WIDTH || position.y >= camera.y + WINDOW_HEIGHT)
            return;
        int draw_x = position.x - camera.x;
        int draw_y = position.y - camera.y;
        al_draw_filled_circle(draw_x, draw_y, size / 2, color);
    }
    virtual void update_hitbox() = 0;
    void move(entity ** entities, coordinate player_hitbox_start, coordinate player_hitbox_end)
    {
        if(!exist)
            return;
        move_in_direction(direction, entities, player_hitbox_start, player_hitbox_end);
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
