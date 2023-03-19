#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <random>

#include <iostream>
using std::cout;

#define WIDTH 1500
#define HEIGHT 800

#define BAR_HEIGHT 200
#define BAR_WIDTH 20

#define BALL_SIZE 20

bool numbers[10][5][4] = 
{
{{1, 1, 1, 1},
{1, 0, 0, 1},
{1, 0, 0, 1},
{1, 0, 0, 1},
{1, 1, 1, 1}},

{{0, 1, 1, 0},
{1, 0, 1, 0},
{0, 0, 1, 0},
{0, 0, 1, 0},
{1, 1, 1, 1}},

{{1, 1, 1, 1},
{0, 0, 0, 1},
{1, 1, 1, 1},
{1, 0, 0, 0},
{1, 1, 1, 1}},

{{1, 1, 1, 1},
{0, 0, 0, 1},
{1, 1, 1, 1},
{0, 0, 0, 1},
{1, 1, 1, 1}},

{{1, 0, 0, 1},
{1, 0, 0, 1},
{1, 1, 1, 1},
{0, 0, 0, 1},
{0, 0, 0, 1}},

{{1, 1, 1, 1},
{1, 0, 0, 0},
{1, 1, 1, 1},
{0, 0, 0, 1},
{1, 1, 1, 1}},

{{1, 1, 1, 1},
{1, 0, 0, 0},
{1, 1, 1, 1},
{1, 0, 0, 1},
{1, 1, 1, 1}},

{{1, 1, 1, 1},
{0, 0, 0, 1},
{0, 0, 0, 1},
{0, 0, 0, 1},
{0, 0, 0, 1}},

{{1, 1, 1, 1},
{1, 0, 0, 1},
{1, 1, 1, 1},
{1, 0, 0, 1},
{1, 1, 1, 1}},

{{1, 1, 1, 1},
{1, 0, 0, 1},
{1, 1, 1, 1},
{0, 0, 0, 1},
{1, 1, 1, 1}},

};

class pong_game{
private:
	ALLEGRO_DISPLAY * display;		
	std::mutex mutex_display;
	std::condition_variable cv_display;
	bool display_set = false;
	
	std::mutex mutex_end;
	std::condition_variable cv_end;
	bool game_end = false;
	
	std::mutex mutex_left;
	int left_direction = 0;
	int left_position = HEIGHT / 2;

	std::mutex mutex_right;
	int right_direction = 0;
	int right_position = HEIGHT / 2;
	
	std::mutex mutex_ball;
	double ball_x = WIDTH / 2;
	double ball_y = HEIGHT / 2;
	double ball_direction_x = 1;
	double ball_direction_y = 0;

	int left_score = 0;
	int right_score = 0;
public:
	void init()
	{
	}
	
	void draw()
	{
		ALLEGRO_COLOR background_color = al_map_rgb(0, 0, 0);
		ALLEGRO_COLOR color = al_map_rgb(255, 255, 255);
		ALLEGRO_COLOR gr = al_map_rgb(150, 150, 150);
		ALLEGRO_COLOR bl = al_map_rgb(0, 0, 0);
		
		al_clear_to_color(background_color);
		
		for(int j = 0; j < 4; j++)
		{
			for(int i = 0; i < 5; i++)
			{
				ALLEGRO_COLOR tmp;
				if(numbers[left_score % 10][i][j])
					tmp = gr;
				else
					tmp = bl;
				al_draw_filled_rectangle(WIDTH / 4 + BALL_SIZE * j + BALL_SIZE * 5, HEIGHT / 3 + BALL_SIZE * i, WIDTH / 4 + BALL_SIZE * (j + 1) + BALL_SIZE * 5,  HEIGHT / 3 + BALL_SIZE * (i + 1), tmp);
		
			}
		}
		
		for(int j = 0; j < 4; j++)
		{
			for(int i = 0; i < 5; i++)
			{
				ALLEGRO_COLOR tmp;
				if(numbers[left_score / 10][i][j])
					tmp = gr;
				else
					tmp = bl;
				al_draw_filled_rectangle(WIDTH / 4 + BALL_SIZE * j, HEIGHT / 3 + BALL_SIZE * i, WIDTH / 4 + BALL_SIZE * (j + 1),  HEIGHT / 3 + BALL_SIZE * (i + 1), tmp);
		
			}
		}

		for(int j = 0; j < 4; j++)
		{
			for(int i = 0; i < 5; i++)
			{
				ALLEGRO_COLOR tmp;
				if(numbers[right_score % 10][i][j])
					tmp = gr;
				else
					tmp = bl;
				al_draw_filled_rectangle((WIDTH * 3) / 4 + BALL_SIZE * j, HEIGHT / 3 + BALL_SIZE * i, (WIDTH * 3) / 4 + BALL_SIZE * (j + 1),  HEIGHT / 3 + BALL_SIZE * (i + 1), tmp);
		
			}
		}
		
		for(int j = 0; j < 4; j++)
		{
			for(int i = 0; i < 5; i++)
			{
				ALLEGRO_COLOR tmp;
				if(numbers[right_score / 10][i][j])
					tmp = gr;
				else
					tmp = bl;
				al_draw_filled_rectangle((WIDTH * 3) / 4 + BALL_SIZE * j - BALL_SIZE * 5, HEIGHT / 3 + BALL_SIZE * i, (WIDTH * 3) / 4 + BALL_SIZE * (j + 1) - BALL_SIZE * 5,  HEIGHT / 3 + BALL_SIZE * (i + 1), tmp);
		
			}
		}
		al_draw_filled_rectangle(WIDTH / 2 - BAR_WIDTH / 2, 0, WIDTH / 2 + BAR_WIDTH / 2, HEIGHT, gr);
		{
			std::unique_lock<std::mutex> lock(mutex_left);
			al_draw_filled_rectangle(0, left_position - BAR_HEIGHT / 2, BAR_WIDTH, left_position + BAR_HEIGHT / 2, color);
		}	
		{
			std::unique_lock<std::mutex> lock(mutex_right);
			al_draw_filled_rectangle(WIDTH - BAR_WIDTH, right_position - BAR_HEIGHT / 2, WIDTH, right_position + BAR_HEIGHT / 2, color);
		}
		{
			std::unique_lock<std::mutex> lock(mutex_right);
			al_draw_filled_rectangle(ball_x - BALL_SIZE / 2, ball_y - BALL_SIZE / 2, ball_x + BALL_SIZE / 2, ball_y + BALL_SIZE / 2, color);	
		}
		al_flip_display();
	
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

	
	void wait_for_end()
	{
		std::unique_lock<std::mutex> lock(mutex_end);
		cv_end.wait(lock, [this]{return game_end;});
	}
	
	void end()
	{
		cout << "GAME ENDED!\n";
		cout << "SCORE: " << left_score << " - " << right_score << "\n";
		std::unique_lock<std::mutex> lock(mutex_end);
		game_end = true;
		cv_end.notify_all();
	}
	
	void left_dir_set(int x)
	{
		std::unique_lock<std::mutex> lock(mutex_left);
		left_direction += x;
	}

	void right_dir_set(int x)
	{
		std::unique_lock<std::mutex> lock(mutex_right);
		right_direction += x;
	}
	
	bool is_ended()
	{
		std::unique_lock<std::mutex> lock(mutex_end);
		return game_end;
	}
	
	void bars_manager()
	{
		bool run = true;
		while(run)
		{
			run = !is_ended();
			{
				std::unique_lock<std::mutex> lock(mutex_left);		
				left_position += left_direction;
				left_position = std::min(left_position, HEIGHT - BAR_HEIGHT / 2);
				left_position = std::max(left_position, BAR_HEIGHT / 2);
			}
			{
				std::unique_lock<std::mutex> lock(mutex_right);			
				right_position += right_direction;
				right_position = std::min(right_position, HEIGHT - BAR_HEIGHT / 2);
				right_position = std::max(right_position, BAR_HEIGHT / 2);
			}
			usleep(5000);
		}
	}
	
	void ball_manager()
	{
		bool run = true;
		while(run)
		{
			run = !is_ended();
			{
				std::unique_lock<std::mutex> lock(mutex_ball);			
				ball_x += ball_direction_x;
				ball_y += ball_direction_y;
				if(ball_x <= BAR_WIDTH + BALL_SIZE / 2)
				{
					std::unique_lock<std::mutex> lock2(mutex_left);			
					if(abs(ball_y - left_position) <= BAR_HEIGHT / 2)
					{
						ball_direction_x *= -1;
						ball_direction_y = (ball_y - left_position)  / (BAR_HEIGHT / 8);
					}
				}
				if(ball_x >= WIDTH - BAR_WIDTH - BALL_SIZE / 2)
				{
					std::unique_lock<std::mutex> lock2(mutex_right);			
					if(abs(ball_y - right_position) <= BAR_HEIGHT / 2)
					{
						ball_direction_x *= -1;
						ball_direction_y = (ball_y - right_position) / (BAR_HEIGHT / 8);
					}
				}
				if(ball_y <= BALL_SIZE / 2)
					ball_direction_y *= -1;
				if(ball_y >= HEIGHT - BALL_SIZE / 2)
					ball_direction_y *= -1;
				if(ball_x <= 0)
				{
					ball_reset();
					right_score++;
				}
				if(ball_x >= WIDTH)
				{
					ball_reset();
					left_score++;
				}
			}
			usleep(5000);
		}
	}
	
	void ball_reset()
	{
		std::unique_lock<std::mutex> lock2(mutex_right);
		ball_x = WIDTH / 2;
		ball_y = HEIGHT / 2;
		ball_direction_x = 1;
		ball_direction_y = 0;
	}
};

void ball_manager(pong_game &game)
{
	game.ball_manager();
}

void player_input_manager(pong_game &game)
{

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
						game.left_dir_set(-1);
						break;
						
					case ALLEGRO_KEY_S:
						game.left_dir_set(1);
						break;
					
					case ALLEGRO_KEY_UP:
						game.right_dir_set(-1);
						break;
						
					case ALLEGRO_KEY_DOWN:
						game.right_dir_set(1);
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
					
			case ALLEGRO_EVENT_KEY_UP:
				switch(event.keyboard.keycode)
				{
					case ALLEGRO_KEY_W:
						game.left_dir_set(1);
						break;
						
					case ALLEGRO_KEY_S:
						game.left_dir_set(-1);
						break;
						
					case ALLEGRO_KEY_UP:
						game.right_dir_set(1);
						break;
						
					case ALLEGRO_KEY_DOWN:
						game.right_dir_set(-1);
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

void create_display(pong_game & game)
{
	al_set_new_display_flags(ALLEGRO_WINDOWED);
	ALLEGRO_DISPLAY* disp = al_create_display(WIDTH, HEIGHT);
	al_init_primitives_addon();
	game.set_display(disp);
	while(!game.is_ended())
	{
		game.draw();
		//TODO
		usleep(1000);
	}

	game.wait_for_end();
}

void init(pong_game & game)
{
	al_init();
	al_install_keyboard();
	al_install_mouse();
	game.init();
}

void bars_wraper(pong_game & game)
{
	game.bars_manager();
}

int main()
{
	pong_game game;
	init(game);
	std::thread display([&game]{create_display(game);});
	std::thread bars([&game]{bars_wraper(game);});
	std::thread ball([&game]{ball_manager(game);});
	std::thread player([&game]{player_input_manager(game);});

	bars.join();
	ball.join();
	player.join();
	display.join();	
	return 0;
}
