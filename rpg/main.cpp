#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <random>
#include <iostream>
#include <queue>
#include "input.h"
#include "game.h"
#include "const.h"

void init(game & g)
{
    al_init();
    al_init_image_addon();
    al_init_primitives_addon();
    al_install_mouse();
    al_install_keyboard();
    g.set();
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
    init(g);

    std::thread display([&g]{create_display(g);});
    std::thread input([&g]{player_input_manager(g);});
    std::thread game_loop([&g]{g.game_loop();});

    game_loop.join();
    input.join();
    display.join();
    return 0;
}
