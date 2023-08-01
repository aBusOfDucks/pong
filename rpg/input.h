#ifndef __INPUT_H__
#define __INPUT_H__

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <random>
#include <iostream>
#include <queue>
#include "game.h"

void player_input_manager(game & g)
{
    g.get_display();
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_display_event_source(g.get_display()));
    ALLEGRO_EVENT event;
    bool run = true;
    while(run)
    {
        al_wait_for_event(queue, &event);
        switch(event.type)
        {
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                if(event.mouse.button == 1)
                    g.click(event.mouse.x, event.mouse.y, MAGIC_ATTACK);
                else
                    g.click(event.mouse.x, event.mouse.y, FIRE_ATTACK);
                break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                g.end();
                run = false;
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
                switch(event.keyboard.keycode)
                {
                    case ALLEGRO_KEY_W:
                        g.change_direction(UP);
                        break;

                    case ALLEGRO_KEY_S:
                        g.change_direction(DOWN);
                        break;

                    case ALLEGRO_KEY_A:
                        g.change_direction(LEFT);
                        break;

                    case ALLEGRO_KEY_D:
                        g.change_direction(RIGHT);
                        break;

                    case ALLEGRO_KEY_1:
                        g.player_change_weapon(1);
                        break;

                    case ALLEGRO_KEY_2:
                        g.player_change_weapon(2);
                        break;

                    case ALLEGRO_KEY_3:
                        g.player_change_weapon(3);
                        break;

                    case ALLEGRO_KEY_TAB:
                    case ALLEGRO_KEY_LSHIFT:
                    case ALLEGRO_KEY_RSHIFT:
                    case ALLEGRO_KEY_LCTRL:
                    case ALLEGRO_KEY_RCTRL:
                    case ALLEGRO_KEY_ALT:
                    case ALLEGRO_KEY_ALTGR:
                        break;

                    case ALLEGRO_KEY_ESCAPE:
                        g.end();
                        run = false;
                        break;
                }
                break;
            case ALLEGRO_EVENT_KEY_UP:
                switch(event.keyboard.keycode)
                {
                    case ALLEGRO_KEY_W:
                        g.change_direction(DOWN);
                        break;

                    case ALLEGRO_KEY_S:
                        g.change_direction(UP);
                        break;

                    case ALLEGRO_KEY_A:
                        g.change_direction(RIGHT);
                        break;

                    case ALLEGRO_KEY_D:
                        g.change_direction(LEFT);
                        break;
                }
                break;

        }
    }
    al_destroy_event_queue(queue);
}

#endif /* __INPUT_H__ */