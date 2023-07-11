#ifndef __CONST_H__
#define __CONST_H__

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

#define MAP_WIDTH 51
#define MAP_HEIGHT 51
#define MAP_CELL_SIZE 30
#define MAP_COLOR al_map_rgb(0, 255, 0)

#define MAGIC_PROJECTILE_SIZE 3
#define MAGIC_PROJECTILE_SPEED 10
#define MAGIC_PROJECTILE_COLOR al_map_rgb(0, 0, 255)

#define FIRE_PROJECTILE_SIZE 6
#define FIRE_PROJECTILE_SPEED 20
#define FIRE_PROJECTILE_COLOR al_map_rgb(255, 100, 0)

#define MAGIC_ATACK 0
#define FIRE_ATACK 1

#define MAX_PROJECTILES 1000

#define PLAYER_COLOR al_map_rgb(255, 0, 0)

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define NONE 4

#define FPS 100
#define TPS 20

#endif /* __CONST_H__ */