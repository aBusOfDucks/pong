#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "projectile.h"

class weapon{
protected:
    ALLEGRO_BITMAP ** bitmaps;

public:
    virtual void attack(int x, int y, int dx, int dy, int mode, projectile * destination) = 0;
};

#endif //__WEAPON_H__

