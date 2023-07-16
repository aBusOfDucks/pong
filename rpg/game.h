#ifndef __GAME_H__
#define __GAME_H__

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <random>
#include <iostream>
#include <queue>
#include "const.h"
#include "coordinate.h"
#include "player.h"
#include "projectile.h"
#include "magic_projectile.h"
#include "fire_projectile.h"
#include "entity.h"
#include "tree.h"
#include "bush.h"
#include <set>

class game{
private:
    ALLEGRO_DISPLAY * display;
    std::mutex mutex_display;
    std::condition_variable cv_display;
    bool display_set = false;

    std::mutex mutex_end;
    bool game_ended = false;

    coordinate camera_position;

    player * p;
    int player_direction;

    std::mutex mutex_projectiles;
    projectile projectiles[MAX_PROJECTILES];
    bool projectile_slot_used[MAX_PROJECTILES];
    int used_projectiles = 0;

    entity * entities[MAX_ENTITIES];
    bool entity_slot_used[MAX_ENTITIES];
    int used_entities = 0;

    void move()
    {
        p->move(entities);
        camera_position = p->get_position() - coordinate(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
        camera_position.trim(MAP_WIDTH - WINDOW_WIDTH, MAP_HEIGHT - WINDOW_HEIGHT);
    }

    void tick()
    {
        move();
        {
            std::unique_lock <std::mutex> lock(mutex_projectiles);
            for (int i = 0; i < MAX_PROJECTILES; i++)
            {
                if (projectile_slot_used[i])
                {
                    projectiles[i].move(entities);
                    if (!projectiles[i].check())
                    {
                        projectile_slot_used[i] = false;
                        used_projectiles--;
                    }
                }
            }
        }
    }

public:
    void draw()
    {
        al_clear_to_color(MAP_COLOR);
        /*
        coordinate player_position = p->get_position();
        coordinate relative_position = player_position - camera_position;

        if(relative_position.x >= 0 && relative_position.y >= 0)
        {
            if(relative_position.x < MAP_WIDTH && relative_position.y <= MAP_HEIGHT)
            {
                int draw_x = relative_position.x * MAP_CELL_SIZE;
                int draw_y = relative_position.y * MAP_CELL_SIZE;
                al_draw_filled_rectangle(draw_x, draw_y, draw_x + MAP_CELL_SIZE, draw_y +  MAP_CELL_SIZE, PLAYER_COLOR);
            }
        }*/
        p->draw(camera_position);
        {
            std::unique_lock<std::mutex> lock(mutex_projectiles);
            for (int i = 0; i < MAX_PROJECTILES; i++)
            {
                if (projectile_slot_used[i])
                {
                    projectiles[i].draw(camera_position);
                }
            }
        }
        for(int i = 0; i < MAX_ENTITIES; i++)
        {
            if(entity_slot_used[i])
            {
                entities[i]->draw(camera_position);
            }
        }
        al_flip_display();
    }

    void set(player * pl)
    {
        p = pl;
        std::unique_lock<std::mutex> lock(mutex_projectiles);
        used_projectiles = 0;
        for(int i = 0; i < MAX_PROJECTILES; i++)
            projectile_slot_used[i] = false;

        std::random_device dev;
        std::mt19937 rng;
        rng = std::mt19937(dev());
        std::uniform_int_distribution<std::mt19937::result_type> entity_x_generator;
        std::uniform_int_distribution<std::mt19937::result_type> entity_y_generator;
        std::uniform_int_distribution<std::mt19937::result_type> entity_type_generator;

        entity_x_generator = std::uniform_int_distribution<std::mt19937::result_type>(0, MAP_WIDTH);
        entity_y_generator = std::uniform_int_distribution<std::mt19937::result_type>(0, MAP_HEIGHT);
        entity_type_generator = std::uniform_int_distribution<std::mt19937::result_type>(0, ENTITIES_NUMBER_OF_TYPES - 1);
        for(int i = 0; i < MAX_ENTITIES; i++)
        {
            int type = entity_type_generator(rng);
            if(type == BUSH_TYPE)
            {
                entities[i] = new bush(entity_x_generator(rng), entity_y_generator(rng));
                used_entities++;
                entity_slot_used[i] = true;
            }
            if(type == TREE_TYPE)
            {
                entities[i] = new tree(entity_x_generator(rng), entity_y_generator(rng));
                used_entities++;
                entity_slot_used[i] = true;
            }
        }
    }

    void set_display(ALLEGRO_DISPLAY * d)
    {
        std::unique_lock<std::mutex> lock(mutex_display);
        display = d;
        display_set = true;
        cv_display.notify_all();
    }

    ALLEGRO_DISPLAY * get_display()
    {
        std::unique_lock<std::mutex> lock(mutex_display);
        cv_display.wait(lock, [this]{return display_set;});
        return display;
    }

    void end()
    {
        std::unique_lock<std::mutex> lock(mutex_end);
        game_ended = true;
    }

    bool is_ended()
    {
        std::unique_lock<std::mutex> lock(mutex_end);
        return game_ended;
    }

    void game_loop()
    {
        bool run = true;
        while(run)
        {
            tick();
            usleep(1000000 / TPS);
            {
                std::unique_lock<std::mutex> lock(mutex_end);
                run = !game_ended;
            }
        }
    }

    void change_direction(int dir)
    {
        if(dir == UP)
        {
            p->change_direction(0, -1);
        }
        if(dir == DOWN)
        {
            p->change_direction(0, 1);
        }
        if(dir == LEFT)
        {
            p->change_direction(-1, 0);
        }
        if(dir == RIGHT)
        {
            p->change_direction(1, 0);
        }
    }

    void click(int x, int y, int type)
    {
        std::unique_lock<std::mutex> lock(mutex_projectiles);
        if(used_projectiles < MAX_PROJECTILES)
        {
            for(int i = 0; i < MAX_PROJECTILES; i++)
                if(!projectile_slot_used[i])
                {
                    projectile_slot_used[i] = true;
                    int poz_x = p->get_position().x + PLAYER_SIZE / 2;
                    int poz_y = p->get_position().y + PLAYER_SIZE / 2;
                    double dx = x + camera_position.x - poz_x;
                    double dy = y + camera_position.y - poz_y;
                    if(type == MAGIC_ATACK)
                    {
                        magic_projectile mp;
                        mp.set(poz_x, poz_y, dx, dy);
                        projectiles[i] = mp;
                    }
                    if(type == FIRE_ATACK)
                    {
                        fire_projectile fp;
                        fp.set(poz_x, poz_y, dx, dy);
                        projectiles[i] = fp;
                    }
                    used_projectiles++;
                    i = MAX_PROJECTILES;
                }
        }
    }
};

#endif /* __GAME_H__ */