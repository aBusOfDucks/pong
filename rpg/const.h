#ifndef __CONST_H__
#define __CONST_H__

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

#define MAP_WIDTH 51
#define MAP_HEIGHT 51
#define MAP_CELL_SIZE 30
#define PROJECTILE_SIZE 2

#define PLAYER_COLOR al_map_rgb(255, 0, 0)
#define MAP_COLOR al_map_rgb(0, 255, 0)
#define PROJECTILE_COLOR al_map_rgb(0, 0, 255)

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define NONE 4

#define FPS 100
#define TPS 5
#define MAX_PROJECTILES 1000
#define PROJECTILE_SPEED 10

#endif /* __CONST_H__ */