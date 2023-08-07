#ifndef __SUPER_WAND_H__
#define __SUPER_WAND_H__

#include "weapon.h"
#include "fire_projectile.h"
#include "magic_projectile.h"

class super_wand : public weapon {

public:
    super_wand(ALLEGRO_BITMAP ** bitmaps)
    {
        this->bitmaps = bitmaps;
    }

    void attack(int x, int y, int dx, int dy, int mode, projectile * destination) override
    {
        if(mode == FIRE_ATTACK)
        {
            fire_projectile fp(x, y, dx, dy, bitmaps);
            (*destination) = fp;
        }
        if(mode == MAGIC_ATTACK)
        {
            magic_projectile mp(x, y, dx, dy, bitmaps);
            (*destination) = mp;
        }
    }
};
#endif //__SUPER_WAND_H__
