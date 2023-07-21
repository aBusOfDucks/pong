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
#define MAP_COLOR al_map_rgb(0, 100, 0)

/* PROJECTILES */

#define MAX_PROJECTILES 100

#define MAGIC_ATACK 0
#define FIRE_ATACK 1

#define MAGIC_PROJECTILE_SIZE 3
#define MAGIC_PROJECTILE_SPEED 1
#define MAGIC_PROJECTILE_COLOR al_map_rgb(0, 200, 250)
#define MAGIC_PROJECTILE_LIFETIME 3
#define MAGIC_PROJECTILE_RANGE (TPS * MAGIC_PROJECTILE_LIFETIME)
#define MAGIC_TYPE 0

#define FIRE_PROJECTILE_SIZE 6
#define FIRE_PROJECTILE_SPEED 2
#define FIRE_PROJECTILE_COLOR al_map_rgb(255, 100, 0)
#define FIRE_PROJECTILE_LIFETIME 1
#define FIRE_PROJECTILE_RANGE (TPS * FIRE_PROJECTILE_LIFETIME)
#define FIRE_TYPE 1

/* ENTITIES */

#define MAX_ENTITIES 250

#define TREE_TYPE 0
#define BUSH_TYPE 1
#define PIG_TYPE 2
#define ROCK_TYPE 3
#define ORC_TYPE 4

#define ENTITIES_NUMBER_OF_TYPES 5

    /* OBSTACLES */

#define TREE_TRUNK_HEIGHT 10
#define TREE_TRUNK_WIDTH 6
#define TREE_LEAVES_HEIGHT 20
#define TREE_LEAVES_WIDTH 20
#define TREE_TRUNK_COLOR al_map_rgb(255, 200, 0)
#define TREE_LEAVES_COLOR al_map_rgb(0, 255, 0)

#define BUSH_SIZE 25
#define BUSH_COLOR al_map_rgb(0, 200, 0)

#define ROCK_SIZE 30
#define ROCK_COLOR al_map_rgb(150, 150, 150)

    /* ENEMIES */

#define CHANCE_TO_CHANGE_DIRECTION 200

#define PIG_SIZE 20
#define PIG_MAGIC_DAMAGE 25
#define PIG_FIRE_DAMAGE 100
#define PIG_HEALTH 60
#define PIG_COLOR al_map_rgb(255, 0, 150)

#define ORC_SIZE 40
#define ORC_MAGIC_DAMAGE 50
#define ORC_FIRE_DAMAGE 35
#define ORC_HEALTH 300
#define ORC_COLOR al_map_rgb(0, 0, 0)

#define ORC_DIRECTION_UP_LEFT 0
#define ORC_DIRECTION_UP_RIGHT 1
#define ORC_DIRECTION_DOWN_LEFT 2
#define ORC_DIRECTION_DOWN_RIGHT 3
#define ORC_DIRECTION_NONE 4
#define ORC_DIRECTIONS_NUMBER 5

/* PLAYER */

#define PLAYER_SIZE 20
#define PLAYER_COLOR al_map_rgb(255, 0, 0)

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define NONE 4
#define DIRECTIONS_NUMBER 5

#endif /* __CONST_H__ */