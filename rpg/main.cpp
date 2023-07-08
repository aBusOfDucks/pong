#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <random>
#include <iostream>
#include <queue>
#include "input.h"
#include "game.h"
#include "const.h"

void init(game & g, player & p)
{
    al_init();
    al_install_keyboard();
    al_install_mouse();
    g.set(&p);
}

void create_display(game & g)
{
    al_set_new_display_flags(ALLEGRO_WINDOWED);
    ALLEGRO_DISPLAY* disp = al_create_display(WINDOW_WIDTH, WINDOW_HEIGHT);
    al_init_primitives_addon();
    g.set_display(disp);
    while(!g.is_ended())
    {
        g.draw();
        usleep(1000000 / FPS);
    }
    al_destroy_display(disp);
}

int main()
{
    game g;
    player p;
    init(g, p);

    std::thread display([&g]{create_display(g);});
    std::thread input([&g]{player_input_manager(g);});
    std::thread game_loop([&g]{g.game_loop();});

    game_loop.join();
    input.join();
    display.join();
    return 0;
}
