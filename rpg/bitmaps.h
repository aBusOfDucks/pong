#ifndef RPG_BITMAPS_H
#define RPG_BITMAPS_H

#include <allegro5/allegro5.h>
#include "const.h"

#define BITMAP_PLAYER_INDEX 0
#define BITMAP_ORC_INDEX 1
#define BITMAP_PIG_INDEX 2
#define BITMAP_ROCK_INDEX 3
#define BITMAP_BUSH_INDEX 4
#define BITMAP_TREE_INDEX 5
#define BITMAP_FIRE_PROJECTILE_INDEX 6
#define BITMAP_MAGIC_PROJECTILE_INDEX 7

void load_bitmaps(ALLEGRO_BITMAP ** bitmaps)
{
    bitmaps[0] = al_load_bitmap(BITMAP_PLAYER_PATH);
    bitmaps[1] = al_load_bitmap(BITMAP_ORC_PATH);
    bitmaps[2] = al_load_bitmap(BITMAP_PIG_PATH);
    bitmaps[3] = al_load_bitmap(BITMAP_ROCK_PATH);
    bitmaps[4] = al_load_bitmap(BITMAP_BUSH_PATH);
    bitmaps[5] = al_load_bitmap(BITMAP_TREE_PATH);
    bitmaps[6] = al_load_bitmap(BITMAP_FIRE_PROJECTILE_PATH);
    bitmaps[7] = al_load_bitmap(BITMAP_MAGIC_PROJECTILE_PATH);
}

#endif //RPG_BITMAPS_H
