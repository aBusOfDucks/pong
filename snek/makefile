CC = g++
FLAGS = -Wall -pthread `pkg-config allegro-5 allegro_primitives-5 --libs --cflags`
BIN = snek
SOURCE = snek.cpp 

all:
	$(CC) $(SOURCE) $(FLAGS) -o $(BIN)
