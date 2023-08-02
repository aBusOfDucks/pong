#ifndef RPG_BITMAPS_H
#define RPG_BITMAPS_H

#include <allegro5/allegro5.h>
#include "const.h"
#include <iostream>

#define BITMAP_PLAYER_INDEX 0
#define BITMAP_ORC_INDEX 1
#define BITMAP_PIG_INDEX 2
#define BITMAP_ROCK_INDEX 3
#define BITMAP_BUSH_INDEX 4
#define BITMAP_TREE_INDEX 5
#define BITMAP_FIRE_PROJECTILE_INDEX 6
#define BITMAP_MAGIC_PROJECTILE_INDEX 7
#define BITMAP_TREE_ON_FIRE_INDEX 8
#define BITMAP_BUSH_ON_FIRE_INDEX 9
#define BITMAP_BUSH_NO_BERRIES_INDEX 10
#define BITMAP_BUSH_NO_BERRIES_ON_FIRE_INDEX 11
#define BITMAP_MAP_INDEX 12
#define BITMAP_ENTITY_BAN_MAP_INDEX 13
#define BITMAP_ORC_BAN_MAP_INDEX 14
#define BITMAP_PLAYER_WITH_MAGIC_WAND_INDEX 15
#define BITMAP_PLAYER_WITH_FIRE_WAND_INDEX 16
#define BITMAP_WATER_MAP_INDEX 17
#define BITMAP_PLANT_BAN_MAP_INDEX 18
#define BITMAP_ROCK_BAN_MAP_INDEX 19

bool check_ban(ALLEGRO_BITMAP ** bitmaps, int index, int x, int y)
{
    if(x < 0 || y < 0)
        return false;
    if(x >= al_get_bitmap_width(bitmaps[index]))
        return false;
    if(y >= al_get_bitmap_height(bitmaps[index]))
        return false;
    ALLEGRO_COLOR px = al_get_pixel(bitmaps[index], x, y);
    unsigned char r = 0, g = 0, b = 0;
    al_unmap_rgb(px, &r, &g, &b);
    if(g == 0)
        return true;
    return false;
}

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
    bitmaps[8] = al_load_bitmap(BITMAP_TREE_ON_FIRE_PATH);
    bitmaps[9] = al_load_bitmap(BITMAP_BUSH_ON_FIRE_PATH);
    bitmaps[10] = al_load_bitmap(BITMAP_BUSH_NO_BERRIES_PATH);
    bitmaps[11] = al_load_bitmap(BITMAP_BUSH_NO_BERRIES_ON_FIRE_PATH);
    bitmaps[12] = al_load_bitmap(BITMAP_MAP_PATH);
    bitmaps[13] = al_load_bitmap(BITMAP_ENTITY_BAN_MAP_PATH);
    bitmaps[14] = al_load_bitmap(BITMAP_ORC_BAN_MAP_PATH);
    bitmaps[15] = al_load_bitmap(BITMAP_PLAYER_WITH_MAGIC_WAND_PATH);
    bitmaps[16] = al_load_bitmap(BITMAP_PLAYER_WITH_FIRE_WAND_PATH);
    bitmaps[17] = al_load_bitmap(BITMAP_WATER_MAP_PATH);
    bitmaps[18] = al_load_bitmap(BITMAP_PLANT_BAN_MAP_PATH);
    bitmaps[19] = al_load_bitmap(BITMAP_ROCK_BAN_MAP_PATH);

    for(int i = 0; i < BITMAPS_NUMBER; i++)
    {
        al_lock_bitmap(bitmaps[i], ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READONLY);
    }
}

#endif //RPG_BITMAPS_H
