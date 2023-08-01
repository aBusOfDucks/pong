#ifndef __FIRE_WAND_H__
#define __FIRE_WAND_H__

#include "weapon.h"
#include "fire_projectile.h"

class fire_wand : public weapon {

public:
    fire_wand(ALLEGRO_BITMAP ** bitmaps)
    {
        this->bitmaps = bitmaps;
    }

    void attack(int x, int y, int dx, int dy, int mode, projectile * destination) override
    {
        fire_projectile fp(x, y, dx, dy, bitmaps);
        (*destination) = fp;
    }
};



#endif //__FIRE_WAND_H__
