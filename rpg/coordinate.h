#ifndef __COORDINATE_H__
#define __COORDINATE_H__

#include "const.h"

class coordinate{
public:
    int x, y;

    coordinate()
    {
        x = 0;
        y = 0;
    }

    coordinate(int poz_x, int poz_y)
    {
        x = poz_x;
        y = poz_y;
    }

    coordinate operator+(coordinate const& c)
    {
        coordinate ans;
        ans.x = x + c.x;
        ans.y = y + c.y;
        return ans;
    }

    coordinate operator-(coordinate const& c)
    {
        coordinate ans;
        ans.x = x - c.x;
        ans.y = y - c.y;
        return ans;
    }

    void change(int dx, int dy)
    {
        x += dx;
        y += dy;
    }

    void trim()
    {
        if (x < 0)
            x = 0;
        if (y < 0)
            y = 0;
        if (x >= MAP_WIDTH)
            x = MAP_WIDTH - 1;
        if (y >= MAP_HEIGHT)
            y = MAP_HEIGHT - 1;
    }
};

#endif /* __COORDINATE_H__ */