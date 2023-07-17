#ifndef __OBSTACLE_H__
#define __OBSTACLE_H__

#include "entity.h"

class obstacle : public entity {
protected:
    bool is_destroyed_by_magic;
    bool is_destroyed_by_fire;

public:
    void hit_by(int type) override
    {
        if(type == FIRE_TYPE && is_destroyed_by_fire)
            kill();
        if(type == MAGIC_TYPE && is_destroyed_by_magic)
            kill();
    }
};

#endif //__OBSTACLE_H__
