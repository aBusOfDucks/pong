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

    coordinate position;

public:

    void move(int direction)
    {
        if(direction == UP)
            position.change(0, -1);
        if(direction == DOWN)
            position.change(0, 1);
        if(direction == RIGHT)
            position.change(1, 0);
        if(direction == LEFT)
            position.change(-1, 0);
        position.trim();
    }

    coordinate get_position()
    {
        return position;
    }

};

#endif /* __PLAYER_H__ */