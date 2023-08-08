#ifndef __DEATH_WAND_H__
#define __DEATH_WAND_H__

#include "weapon.h"
#include "death_projectile.h"

class death_wand : public weapon {

public:
    death_wand(ALLEGRO_BITMAP ** bitmaps)
    {
        this->bitmaps = bitmaps;
    }

    void attack(int x, int y, int dx, int dy, int mode, projectile * destination) override
    {
        death_projectile dp(x, y, dx, dy, bitmaps);
        (*destination) = dp;
    }
};

#endif //__DEATH_WAND_H__
