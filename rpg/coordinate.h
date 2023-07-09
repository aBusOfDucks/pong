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

    void set(int new_x, int new_y)
    {
        x = new_x;
        y = new_y;
    }

    void change(int dx, int dy)
    {
        x += dx;
        y += dy;
    }

    void trim(int max_x, int max_y)
    {
        if (x < 0)
            x = 0;
        if (y < 0)
            y = 0;
        if (x >= max_x)
            x = max_x - 1;
        if (y >= max_y)
            y = max_y - 1;
    }

    void trim()
    {
        trim(MAP_WIDTH, MAP_HEIGHT);
    }

    void scale(int m)
    {
        x *= m;
        y *= m;
    }
};

#endif /* __COORDINATE_H__ */