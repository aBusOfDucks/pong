#ifndef __CONST_H__
#define __CONST_H__

#define FPS 100
#define TPS 200

#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 900

#define MAP_WIDTH 1500
#define MAP_HEIGHT 1500
#define MAP_COLOR al_map_rgb(0, 100, 0)

#define MAGIC_PROJECTILE_SIZE 3
#define MAGIC_PROJECTILE_SPEED 1
#define MAGIC_PROJECTILE_COLOR al_map_rgb(0, 100, 255)
#define MAGIC_PROJECTILE_LIFETIME 3
#define MAGIC_PROJECTILE_RANGE (TPS * MAGIC_PROJECTILE_LIFETIME)

#define FIRE_PROJECTILE_SIZE 6
#define FIRE_PROJECTILE_SPEED 2
#define FIRE_PROJECTILE_COLOR al_map_rgb(255, 100, 0)
#define FIRE_PROJECTILE_LIFETIME 1
#define FIRE_PROJECTILE_RANGE (TPS * FIRE_PROJECTILE_LIFETIME)

#define TREE_TRUNK_HEIGHT 10
#define TREE_TRUNK_WIDTH 6
#define TREE_LEAVES_HEIGHT 20
#define TREE_LEAVES_WIDTH 20
#define TREE_TRUNK_COLOR al_map_rgb(255, 200, 0)
#define TREE_LEAVES_COLOR al_map_rgb(0, 255, 0)


#define MAGIC_ATACK 0
#define FIRE_ATACK 1

#define MAX_PROJECTILES 1000
#define MAX_ENTITIES 250

#define PLAYER_SIZE 20
#define PLAYER_COLOR al_map_rgb(255, 0, 0)

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define NONE 4

#endif /* __CONST_H__ */