#ifndef __PLAYER_H__
#define __PLAYER_H__

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

class player{
private:

    std::mutex mutex_position;
    coordinate position;
    int direction_x;
    int direction_y;

public:

    player()
    {
        direction_x = 0;
        direction_y = 0;
        position.set(0, 0);
    }
    void move()
    {
        std::unique_lock<std::mutex> lock(mutex_position);
        position.change(direction_x, direction_y);
        position.trim();
    }

    void change_direction(int dx, int dy)
    {
        std::unique_lock<std::mutex> lock(mutex_position);
        direction_x += dx;
        direction_y += dy;
    }

    coordinate get_position()
    {
        std::unique_lock<std::mutex> lock(mutex_position);
        return position;
    }

};

#endif /* __PLAYER_H__ */