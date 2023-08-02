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
#include "player.h"
#include "magic_projectile.h"
#include "fire_projectile.h"
#include "tree.h"
#include "bush.h"
#include "orc.h"
#include "pig.h"
#include "rock.h"

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

    entity * entities[MAX_ENTITIES];
    bool entity_slot_used[MAX_ENTITIES];
    int used_entities = 0;

    ALLEGRO_BITMAP * bitmaps[BITMAPS_NUMBER];

    int map_width, map_height;

    void move()
    {
        p->move(entities, p);
        camera_position = p->get_position() - coordinate(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
        camera_position.trim(map_width - WINDOW_WIDTH, map_height - WINDOW_HEIGHT);
        camera_position.trim_bottom(0, 0);
    }

    void tick()
    {
        move();
        {
            std::unique_lock <std::mutex> lock(mutex_projectiles);
            for (int i = 0; i < MAX_PROJECTILES; i++)
            {
                if (projectiles[i].does_exist())
                {
                    projectiles[i].move(entities);
                    if (!projectiles[i].check())
                    {
                        projectiles[i].destroy();
                    }
                }
            }
        }
        for(int i = 0; i < MAX_ENTITIES; i++)
        {
            entities[i]->move(entities, p);
        }
    }

public:
    void draw()
    {
        al_draw_bitmap_region(bitmaps[BITMAP_MAP_INDEX], camera_position.x, camera_position.y, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, 0);
        p->draw(camera_position, bitmaps);
        {
            std::unique_lock<std::mutex> lock(mutex_projectiles);
            for (int i = 0; i < MAX_PROJECTILES; i++)
            {
                if (projectiles[i].does_exist())
                {
                    projectiles[i].draw(camera_position, bitmaps);
                }
            }
        }
        for(int i = 0; i < MAX_ENTITIES; i++)
        {
            if(entity_slot_used[i])
            {
                entities[i]->draw(camera_position, bitmaps);
            }
        }
        al_flip_display();
    }

    void player_change_weapon(int num)
    {
        p->change_weapon(num);
    }

    void set()
    {
        load_bitmaps(bitmaps);
        p = new player(bitmaps);
        map_width = al_get_bitmap_width(bitmaps[BITMAP_MAP_INDEX]);
        map_height = al_get_bitmap_height(bitmaps[BITMAP_MAP_INDEX]);

        for(int i = 0; i < MAX_PROJECTILES; i++)
            projectiles[i].destroy();

        std::random_device dev;
        std::mt19937 rng;
        rng = std::mt19937(dev());
        std::uniform_int_distribution<std::mt19937::result_type> entity_x_generator;
        std::uniform_int_distribution<std::mt19937::result_type> entity_y_generator;
        std::uniform_int_distribution<std::mt19937::result_type> entity_type_generator;

        entity_x_generator = std::uniform_int_distribution<std::mt19937::result_type>(0, map_width);
        entity_y_generator = std::uniform_int_distribution<std::mt19937::result_type>(0, map_height);
        entity_type_generator = std::uniform_int_distribution<std::mt19937::result_type>(0, ENTITIES_NUMBER_OF_TYPES - 1);
        for(int i = 0; i < MAX_ENTITIES; i++)
        {
            int type = entity_type_generator(rng);
            if(type == ENTITY_TYPE_BUSH)
            {
                entities[i] = new bush(entity_x_generator(rng), entity_y_generator(rng), bitmaps);
            }
            if(type == ENTITY_TYPE_TREE)
            {
                entities[i] = new tree(entity_x_generator(rng), entity_y_generator(rng), bitmaps);
            }
            if(type == ENTITY_TYPE_PIG)
            {
                entities[i] = new pig(entity_x_generator(rng), entity_y_generator(rng), bitmaps);
            }
            if(type == ENTITY_TYPE_ROCK)
            {
                entities[i] = new rock(entity_x_generator(rng), entity_y_generator(rng), bitmaps);
            }
            if(type == ENTITY_TYPE_ORC)
            {
                entities[i] = new orc(entity_x_generator(rng), entity_y_generator(rng), bitmaps);
            }
            used_entities++;
            entity_slot_used[i] = true;
            for(int j = 0; j < i; j++)
            {
                if(entities[i]->entity_collide(entities[j]) || !entities[i]->check_map_position())
                {
                    used_entities--;
                    j = i;
                    i--;
                }
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

    void click(int x, int y, int mode)
    {
        std::unique_lock<std::mutex> lock(mutex_projectiles);
        p->use_weapon(x, y, mode, projectiles, camera_position);
    }
};

#endif /* __GAME_H__ */