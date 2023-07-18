#ifndef __PIG_H__
#define __PIG_H__

#include "enemy.h"
#include "const.h"

class pig : public enemy {
public:
    pig(double x, double y)
    {
        position.set(x, y);
        size = PIG_SIZE;
        hitbox_start.set(x - size / 2, y - size / 2);
        hitbox_end.set(x + size / 2, y + size / 2);
        health_points = PIG_HEALTH;
        fire_damage = PIG_FIRE_DAMAGE;
        magic_damage = PIG_MAGIC_DAMAGE;
        color = PIG_COLOR;
        can_player_pass = false;
    }
    void update_hitbox()
    {
        hitbox_start.set(position.x - size / 2, position.y - size / 2);
        hitbox_end.set(position.x + size / 2, position.y + size / 2);
    }
};

#endif //__PIG_H__
