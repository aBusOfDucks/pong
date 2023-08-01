#ifndef __MAGIC_WAND_H__
#define __MAGIC_WAND_H__

#include "weapon.h"
#include "magic_projectile.h"

class magic_wand : public weapon {
public:
    magic_wand(ALLEGRO_BITMAP ** bitmaps)
    {
        this->bitmaps = bitmaps;
    }

    void attack(int x, int y, int dx, int dy, int mode, projectile * destination) override
    {
        magic_projectile mp(x, y, dx, dy, bitmaps);
        (*destination) = mp;
    }
};

#endif //__MAGIC_WAND_H__

