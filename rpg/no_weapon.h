#ifndef __NO_WEAPON__
#define __NO_WEAPON__

class no_weapon : public weapon {
public:
    no_weapon(ALLEGRO_BITMAP ** bitmaps)
    {
        this->bitmaps = bitmaps;
    }

    void attack(int x, int y, int dx, int dy, int mode, projectile * destination) override
    {
        return;
    }
};

#endif //__NO_WEAPON__
