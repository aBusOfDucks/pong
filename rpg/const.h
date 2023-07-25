#ifndef __CONST_H__
#define __CONST_H__

/* GENERAL */

#define FPS 100
#define TPS 200

/* WINDOW */

#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 900

/* MAP */

#define MAP_WIDTH 1500
#define MAP_HEIGHT 1500
#define MAP_COLOR al_map_rgb(150, 200, 0)

/* PROJECTILES */

#define MAX_PROJECTILES 100

#define MAGIC_ATTACK 0
#define FIRE_ATTACK 1

#define MAGIC_TYPE 0
#define FIRE_TYPE 1

#define MAGIC_PROJECTILE_SPEED 1
#define MAGIC_PROJECTILE_LIFETIME 3
#define MAGIC_PROJECTILE_RANGE (TPS * MAGIC_PROJECTILE_LIFETIME)

#define FIRE_PROJECTILE_SPEED 2
#define FIRE_PROJECTILE_LIFETIME 1
#define FIRE_PROJECTILE_RANGE (TPS * FIRE_PROJECTILE_LIFETIME)

/* ENTITIES */

#define MAX_ENTITIES 250

#define TREE_TYPE 0
#define BUSH_TYPE 1
#define PIG_TYPE 2
#define ROCK_TYPE 3
#define ORC_TYPE 4

#define ENTITIES_NUMBER_OF_TYPES 5

    /* ENEMIES */

#define CHANCE_TO_CHANGE_DIRECTION 200

#define PIG_MAGIC_DAMAGE 25
#define PIG_FIRE_DAMAGE 100
#define PIG_HEALTH 60

#define ORC_MAGIC_DAMAGE 50
#define ORC_FIRE_DAMAGE 35
#define ORC_HEALTH 300

#define ORC_DIRECTION_UP_LEFT 0
#define ORC_DIRECTION_UP_RIGHT 1
#define ORC_DIRECTION_DOWN_LEFT 2
#define ORC_DIRECTION_DOWN_RIGHT 3
#define ORC_DIRECTION_NONE 4
#define ORC_DIRECTIONS_NUMBER 5

/* PLAYER */


#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define NONE 4
#define DIRECTIONS_NUMBER 5

/* BITMAPS */

#define BITMAP_PLAYER_PATH "bitmaps/player.piko"
#define BITMAP_ORC_PATH "bitmaps/orc1.piko"
#define BITMAP_PIG_PATH "bitmaps/pig1.piko"
#define BITMAP_ROCK_PATH "bitmaps/rock1.piko"
#define BITMAP_BUSH_PATH "bitmaps/bush1.piko"
#define BITMAP_TREE_PATH "bitmaps/tree1.piko"
#define BITMAP_FIRE_PROJECTILE_PATH "bitmaps/fire_projectile.piko"
#define BITMAP_MAGIC_PROJECTILE_PATH "bitmaps/magic_projectile.piko"

#define BITMAPS_NUMBER 8

#endif /* __CONST_H__ */