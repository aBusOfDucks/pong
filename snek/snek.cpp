#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <random>
#include <iostream>

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 1200
#define SPEED 100
#define SNEK_SIZE 10
#define SNEK_COLOR al_map_rgb(0, 255, 0)
#define APPLE_COLOR al_map_rgb(255,0, 0)
#define BACKGROUND_COLOR al_map_rgb(0,0, 0)

class snek{
private:
    int board[WINDOW_WIDTH / SNEK_SIZE][WINDOW_HEIGHT / SNEK_SIZE];
    int size;
    int poz_x, poz_y;
    int dx, dy;
    std::random_device dev;
    std::mt19937 rng;
    std::uniform_int_distribution<std::mt19937::result_type> poz_x_generator;
    std::uniform_int_distribution<std::mt19937::result_type> poz_y_generator;
    int apple_x, apple_y;

    void generate_apple()
    {
        apple_x = poz_x;
        apple_y = poz_y;
        while(board[apple_x][apple_y] > 0)
        {
            apple_x = poz_x_generator(rng);
            apple_y = poz_y_generator(rng);
        }
    }

public:
	void draw()
	{
        for(int i = 0; i < WINDOW_WIDTH / SNEK_SIZE; i++)
            for(int j = 0; j < WINDOW_HEIGHT / SNEK_SIZE; j++)
                if(board[i][j] > 0)
		            al_draw_filled_rectangle(i * SNEK_SIZE, j * SNEK_SIZE, (i + 1) * SNEK_SIZE, (j + 1) * SNEK_SIZE, SNEK_COLOR);
        al_draw_filled_rectangle(apple_x * SNEK_SIZE, apple_y * SNEK_SIZE, (apple_x + 1) * SNEK_SIZE, (apple_y + 1) * SNEK_SIZE, APPLE_COLOR);
	}
	
	void set()
	{
        poz_x_generator = std::uniform_int_distribution<std::mt19937::result_type>(0, WINDOW_WIDTH / SNEK_SIZE);
        poz_y_generator = std::uniform_int_distribution<std::mt19937::result_type>(0, WINDOW_HEIGHT / SNEK_SIZE);
        rng = std::mt19937(dev());

        size = 1;
        for(int i = 0; i < WINDOW_WIDTH / SNEK_SIZE; i++)
            for(int j = 0; j < WINDOW_HEIGHT / SNEK_SIZE; j++)
                board[i][j] = 0;
        dx = 1;
        dy = 0;
        poz_x = WINDOW_WIDTH / SNEK_SIZE / 2;
        poz_y = WINDOW_HEIGHT / SNEK_SIZE / 2;
        board[poz_x][poz_y] = size;
        generate_apple();
    }
	
	bool move()
	{
        for(int i = 0; i < WINDOW_WIDTH / SNEK_SIZE; i++)
            for(int j = 0; j < WINDOW_HEIGHT / SNEK_SIZE; j++)
                if(board[i][j] > 0)
                    board[i][j]--;
        poz_x += dx;
        poz_y += dy;
        if(board[poz_x][poz_y] > 0)
            return false;
        board[poz_x][poz_y] = size;
        if(poz_x == apple_x && poz_y == apple_y)
        {
            size++;
            board[poz_x][poz_y]++;
            generate_apple();
        }
        return true;
	}
};

void init(snek * sneak)
{
	al_init();
    sneak->set();
}

void draw(snek * sneak)
{
	al_clear_to_color(BACKGROUND_COLOR);
	sneak->draw();
	al_flip_display();
}

int main()
{
    snek sneak;
	init(&sneak);
	al_set_new_display_flags(ALLEGRO_WINDOWED);
	ALLEGRO_DISPLAY* disp = al_create_display(WINDOW_WIDTH, WINDOW_HEIGHT);
	al_init_primitives_addon();
	draw(&sneak);
	while(true)
	{
        sneak.move();
		draw(&sneak);
		usleep(10000);
	}
	al_destroy_display(disp);
	return 0;
}
