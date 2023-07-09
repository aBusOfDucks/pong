CC = g++
FLAGS = -Wall -pthread `pkg-config allegro-5 allegro_primitives-5 --libs --cflags`
BIN = game
SOURCE = main.cpp input.h game.h const.h player.h coordinate.h projectile.h

all:
	$(CC) $(SOURCE) $(FLAGS) -o $(BIN)
