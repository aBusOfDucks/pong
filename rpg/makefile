CC = g++
FLAGS = -Wall -pthread `pkg-config allegro-5 allegro_primitives-5 --libs --cflags`
BIN = Game
SOURCE = main.cpp input.h game.h const.h player.h coordinate.h projectile.h fire_projectile.h magic_projectile.h entity.h tree.h bush.h

all:
	$(CC) $(SOURCE) $(FLAGS) -o $(BIN)
