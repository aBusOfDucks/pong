#ifndef __COORDINATE_H__
#define __COORDINATE_H__

#include "const.h"

class coordinate{
public:
    double x, y;

    coordinate()
    {
        x = 0;
        y = 0;
    }

    coordinate(double poz_x, double poz_y)
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

    void set(double new_x, double new_y)
    {
        x = new_x;
        y = new_y;
    }

    void change(double dx, double dy)
    {
        x += dx;
        y += dy;
    }

    void trim(int max_x, int max_y)
    {
    /*    if (x < 0)
            x = 0;
        if (y < 0)
            y = 0;*/
        if (x > max_x)
            x = max_x;
        if (y > max_y)
            y = max_y;
    }

    void trim()
    {
        trim(MAP_WIDTH, MAP_HEIGHT);
    }

    void trim_bottom(double min_x, double min_y)
    {
        if(x < min_x)
            x = min_x;
        if(y < min_y)
            y = min_y;
    }

    void scale(double m)
    {
        x *= m;
        y *= m;
    }

    bool in_square(coordinate left_upper, coordinate right_bottom)
    {
        if(x >= left_upper.x && x <= right_bottom.x)
            if(y >= left_upper.y && y <= right_bottom.y)
                return true;
        return false;
    }
};

#endif /* __COORDINATE_H__ */