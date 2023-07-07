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

#define CAMERA_WIDTH WINDOW_WIDTH / MAP_CELL_SIZE
#define CAMERA_HEIGHT WINDOW_HEIGHT / MAP_CELL_SIZE

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

public:
    void draw()
    {
        al_clear_to_color(MAP_COLOR);
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
        }
        al_flip_display();
    }
    void set(player * pl)
    {
        p = pl;
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
    void move(int direction)
    {
        p->move(direction);
        camera_position = p->get_position() - coordinate(CAMERA_WIDTH / 2, CAMERA_HEIGHT / 2);
        camera_position.trim(MAP_WIDTH - CAMERA_WIDTH + 1, MAP_HEIGHT - CAMERA_HEIGHT + 1);
    }
};

#endif /* __GAME_H__ */