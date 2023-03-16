# pong
Simple pong implementation.
Can be compiled with:
g++ -pthread pong.cpp $(pkg-config allegro-5 allegro_primitives-5 --libs --cflags) -o pong
