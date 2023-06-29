#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <random>
#include <iostream>

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 1200
#define SNEK_SPEED 15
#define SNEK_SIZE 60
#define SNEK_COLOR al_map_rgb(0, 255, 0)
#define APPLE_COLOR al_map_rgb(255,0, 0)
#define BACKGROUND_COLOR al_map_rgb(0,0, 0)
#define BOARD_WIDTH WINDOW_WIDTH / SNEK_SIZE
#define BOARD_HEIGHT WINDOW_HEIGHT / SNEK_SIZE


class snek{
private:


    std::mutex mutex_board_size;
    int board[WINDOW_WIDTH / SNEK_SIZE][WINDOW_HEIGHT / SNEK_SIZE];
    int size;

    std::mutex mutex_poz_dir;
    int poz_x, poz_y;
    int dx, dy;
    int apple_x, apple_y;
    bool moved = false;

    std::random_device dev;
    std::mt19937 rng;
    std::uniform_int_distribution<std::mt19937::result_type> apple_generator;


    ALLEGRO_DISPLAY * display;
    std::mutex mutex_display;
    std::condition_variable cv_display;
    bool display_set = false;

    std::mutex mutex_end;
    bool game_ended = false;

    void generate_apple()
    {
        int ax, ay;
        {
            std::unique_lock <std::mutex> lock(mutex_poz_dir);
            ax = poz_x;
            ay = poz_y;
        }
        {
            std::unique_lock <std::mutex> lock(mutex_board_size);
            apple_generator = std::uniform_int_distribution<std::mt19937::result_type>(1, BOARD_WIDTH * BOARD_HEIGHT -
                                                                                          size);
            int temp = apple_generator(rng);
            for (int i = 0; i < BOARD_WIDTH; i++)
            {
                 for (int j = 0; j < BOARD_HEIGHT; j++)
                 {
                     if(board[i][j] == 0)
                         temp--;
                     if(temp == 0)
                     {
                         ax = i;
                         ay = j;
                         i = BOARD_WIDTH;
                         break;
                     }
                 }
            }
        }
        {
            std::unique_lock <std::mutex> lock(mutex_poz_dir);
            apple_x = ax;
            apple_y = ay;
            std::cout << "Apple at: " << ax << " " << ay << "\n";
        }
    }

public:
	void draw()
	{
        al_clear_to_color(BACKGROUND_COLOR);
        {
            std::unique_lock <std::mutex> lock(mutex_board_size);
            for (int i = 0; i < BOARD_WIDTH; i++)
                for (int j = 0; j < BOARD_HEIGHT; j++)
                    if (board[i][j] > 0)
                        al_draw_filled_rectangle(i * SNEK_SIZE, j * SNEK_SIZE, (i + 1) * SNEK_SIZE, (j + 1) * SNEK_SIZE,
                                                 SNEK_COLOR);
        }
        {
            std::unique_lock <std::mutex> lock(mutex_board_size);
            al_draw_filled_rectangle(apple_x * SNEK_SIZE, apple_y * SNEK_SIZE, (apple_x + 1) * SNEK_SIZE,(apple_y + 1) * SNEK_SIZE, APPLE_COLOR);
        }
        al_flip_display();
    }
	
	void set()
	{
        apple_generator = std::uniform_int_distribution<std::mt19937::result_type>(1, BOARD_WIDTH * BOARD_HEIGHT);
        rng = std::mt19937(dev());

        size = 1;
        {
            std::unique_lock <std::mutex> lock(mutex_board_size);
            for (int i = 0; i < BOARD_WIDTH; i++)
                for (int j = 0; j < BOARD_HEIGHT; j++)
                    board[i][j] = 0;
        }
        {
            std::unique_lock <std::mutex> lock(mutex_poz_dir);
            dx = 1;
            dy = 0;
            poz_x = BOARD_WIDTH / 2;
            poz_y = BOARD_HEIGHT / 2;
            board[poz_x][poz_y] = size;
            moved = false;
        }
        generate_apple();
    }
	
	bool move()
	{
        {
            std::unique_lock <std::mutex> lock(mutex_board_size);
            for (int i = 0; i < BOARD_WIDTH; i++)
                for (int j = 0; j < BOARD_HEIGHT; j++)
                    if (board[i][j] > 0)
                        board[i][j]--;
        }
        int x,y;
        int ax, ay;
        bool gen = false;
        {
            std::unique_lock <std::mutex> lock(mutex_poz_dir);
            poz_x += dx;
            poz_y += dy;
            if (poz_x < 0)
                poz_x = BOARD_WIDTH - 1;
            if (poz_x >= BOARD_WIDTH)
                poz_x = 0;
            if (poz_y < 0)
                poz_y = BOARD_HEIGHT - 1;
            if (poz_y >= BOARD_HEIGHT)
                poz_y = 0;
            x = poz_x;
            y = poz_y;
            ax = apple_x;
            ay = apple_y;
            moved = true;
        }
        {
            std::unique_lock <std::mutex> lock(mutex_board_size);
            if (board[x][y] > 0)
                return false;
            board[x][y] = size;
            if(x == ax && y == ay)
            {
                size++;
                board[x][y]++;
                gen = true;
            }
        }
        if(gen)
            generate_apple();
        return true;
	}

    void set_direction(int x, int y)
    {
        std::unique_lock<std::mutex> lock(mutex_poz_dir);
        // TODO: queue orders insted of ignoring
        if(!moved)
            return;
        moved = false;
        if(x == 0 && y != 0)
        {
            if(dx != 0)
            {
                dx = x;
                dy = y;
            }
        }
        if(x != 0 && y == 0)
        {
            if(dy != 0)
            {
                dx = x;
                dy = y;
            }
        }
    }
    void set_display(ALLEGRO_DISPLAY * d)
    {
        std::unique_lock<std::mutex> lock(mutex_display);
        display = d;
        display_set = true;
        cv_display.notify_all();
    }

    ALLEGRO_DISPLAY * get_display()
    {
        std::unique_lock<std::mutex> lock(mutex_display);
        cv_display.wait(lock, [this]{return display_set;});
        return display;
    }

    void end()
    {
        std::unique_lock<std::mutex> lock(mutex_end);
        game_ended = true;
    }

    bool is_ended()
    {
        std::unique_lock<std::mutex> lock(mutex_end);
        return game_ended;
    }
};

void player_input_manager(snek & game)
{
    game.get_display();
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_display_event_source(game.get_display()));
    ALLEGRO_EVENT event;
    bool run = true;
    while(run)
    {
        al_wait_for_event(queue, &event);
        switch(event.type)
        {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                game.end();
                run = false;
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                switch(event.keyboard.keycode)
                {
                    case ALLEGRO_KEY_W:
                        game.set_direction(0, -1);
                        break;

                    case ALLEGRO_KEY_S:
                        game.set_direction(0, 1);
                        break;

                    case ALLEGRO_KEY_A:
                        game.set_direction(-1, 0);
                        break;

                    case ALLEGRO_KEY_D:
                        game.set_direction(1, 0);
                        break;

                    case ALLEGRO_KEY_R:
                        game.set();
                        break;

                    case ALLEGRO_KEY_TAB:
                    case ALLEGRO_KEY_LSHIFT:
                    case ALLEGRO_KEY_RSHIFT:
                    case ALLEGRO_KEY_LCTRL:
                    case ALLEGRO_KEY_RCTRL:
                    case ALLEGRO_KEY_ALT:
                    case ALLEGRO_KEY_ALTGR:
                        break;

                    default:
                        game.end();
                        run = false;
                        break;
                }
                break;
        }
    }
    al_destroy_event_queue(queue);
}

void init(snek * sneak)
{
	al_init();
    al_install_keyboard();
    al_install_mouse();
    sneak->set();
}

void create_display(snek & game)
{
    al_set_new_display_flags(ALLEGRO_WINDOWED);
    ALLEGRO_DISPLAY* disp = al_create_display(WINDOW_WIDTH, WINDOW_HEIGHT);
    al_init_primitives_addon();
    game.set_display(disp);
    while(!game.is_ended())
    {
        game.draw();
        if(!game.move())
        {
            std::cout << "END!\n";
            game.set();
        }
        usleep(1000000 / SNEK_SPEED);
    }

  //  game.wait_for_end();
    al_destroy_display(disp);
}

int main()
{
    snek sneak;
	init(&sneak);
    std::thread display([&sneak]{create_display(sneak);});
    std::thread player([&sneak]{player_input_manager(sneak);});

    player.join();
    display.join();
	return 0;
}
