# pong
Simple pong implementation.
Can be compiled with:
g++ -pthread pong.cpp $(pkg-config allegro-5 allegro_primitives-5 --libs --cflags) -o pong

- Press 'W' and 'S' to move the left paddle;

- Press arrow up and arrow down to move the right paddle;

- Press 'R' to restart;

- Press any other key to quit.
