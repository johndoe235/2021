#include <stdio.h>
#include <SDL.h>

#include "structures.h"

#define SCREEN_WIDTH 700
#define SCREEN_HEIGTH 640
#define PIXEL_SIZE 50

#define PLAYSPACEWIDTH SCREEN_WIDTH
#define PLAYSPACEHEIGHT SCREEN_HEIGTH

#define WIDTH_COUNT PLAYSPACEWIDTH/PIXEL_SIZE
#define HEIGHT_COUNT PLAYSPACEHEIGHT/PIXEL_SIZE

#define MAX_SIZE (WIDTH_COUNT)*(HEIGHT_COUNT)

SDL_Window* my_window;
SDL_Renderer* my_renderer;
SDL_Event e;

SDL_Rect SCREEN[HEIGHT_COUNT][WIDTH_COUNT];


bool init()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("Cannot initialzie SDL! Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		my_window = SDL_CreateWindow(
			"Snake", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGTH, SDL_WINDOW_SHOWN
		);
		if (my_window == NULL)
		{
			printf("SDL Window cannot be created! Error:  %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			my_renderer = SDL_CreateRenderer(my_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (my_renderer == NULL)
			{
				printf("SDL Renderer cannot be created! Error:  %s\n", SDL_GetError());
				success = false;
			}






		}
	}
	return success;
}
void sdl_close()
{
	SDL_DestroyRenderer(my_renderer);
	SDL_DestroyWindow(my_window);
	SDL_Quit();

}
void input(snake* snake, bool* quit)
{
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			*quit = true;
			return;
		}

		if (e.type == SDL_KEYDOWN)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				*quit = true;
				break;

			case SDLK_w:
				if (snake->movement != SOUTH)
					snake->movement = NORTH;
				return;

			case SDLK_d:
				if (snake->movement != WEST)
					snake->movement = EAST;
				return;

			case SDLK_s:
				if (snake->movement != NORTH)
					snake->movement = SOUTH;
				return;

			case SDLK_a:
				if (snake->movement != EAST)
					snake->movement = WEST;
				return;

			default:
				break;


			}
		}

	}
}




bool collision(position* A, position* B)
{
	if (A->x == B->x && A->y == B->y)
		return true;
	else
		return false;
}

void add_size(snake* snake)
{
	if (snake->size == snake->max_size)
	{
		snake->max_size = snake->max_size << 1;

		snake->body = realloc(snake->body, sizeof(position) * snake->max_size);
		
	}
	
	snake->size++;

}

void snake_update(snake* snake)
{
	SDL_SetRenderDrawColor(my_renderer, 255, 0, 0, 255);

	if (snake->alive && snake->body!=NULL)
	{
	
		if (snake->size > 1)
		{
			for (int i = snake->size - 1; i > 0; i--)
			{
				snake->body[i].x = snake->body[i-1].x;
				snake->body[i].y = snake->body[i - 1].y;
			}

		}
		
			switch (snake->movement)
			{
			case NORTH:
				if(snake->body[0].y>0)
				snake->body[0].y -= 1;

				break;
			case WEST:
				if (snake->body[0].x > 0)
				snake->body[0].x -= 1;
				break;
			case SOUTH:
				if (snake->body[0].y < HEIGHT_COUNT-1)
				snake->body[0].y += 1;

				break;
			case EAST:
				if (snake->body[0].x < WIDTH_COUNT-1)
				snake->body[0].x += 1;

				break;
			}
			
		}
	else
	{
		if(snake->size>0)
			snake->size--;
	}
	

	for(int i = snake->size - 1; i >= 0; i--)
	{

		SDL_RenderFillRect(my_renderer, &SCREEN[snake->body[i].y][snake->body[i].x]);
	}
	

}
void reset(snake* snake, rabbit* rabbit)
{

	snake->body[0].x = 1;
	snake->body[0].y = 1;
	snake->movement = EAST;
	snake->size = 1;
	snake->moves_since_last_shortcut = 0;
	rabbit->alive = false;
	snake->alive = true;

}
void rabbit_update(rabbit* rabbit)
{

	if (rabbit->alive)
	{
		SDL_SetRenderDrawColor(my_renderer, 0, 255, 0, 255);
		SDL_RenderFillRect(my_renderer, &SCREEN[rabbit->p.y][rabbit->p.x]);
	}


}
void game_logic(snake* snake,rabbit* rabbit)
{

	if (collision(&rabbit->p, &snake->body[0]))
	{
		add_size(snake);
		rabbit->alive = false;
	}

	if (!rabbit->alive)
	{
		 uint32_t terrible_programming = SDL_GetTicks();
	line_221:

		
		rabbit->p.x = rand() % WIDTH_COUNT;
		rabbit->p.y = rand()%  HEIGHT_COUNT;

		bool legit = true;

		for (int i = 0; i < snake->size;i++)
		{
			if (collision(&rabbit->p, &snake->body[i]))
				legit= false;
		}
		if (!legit)
		{
			if (snake->size<=MAX_SIZE)
				goto line_221;
			
		}

		
	

		
		rabbit->alive = true;
	}

//	if (snake->body[0].x == 0 || snake->body[0].y == 0 || snake->body[0].x == WIDTH_COUNT-1 || snake->body[0].y == HEIGHT_COUNT-1)
		//snake->alive = false;

	for (int i = 1; i < snake->size; i++)
	{
		if (collision(&snake->body[0], &snake->body[i]))
			snake->alive = false;
	}


	


	snake_update(snake);
	if(snake->alive)
	rabbit_update(rabbit);





}







void Game()
{

	
	snake snake;
	snake.body = calloc(10, sizeof(position));
	snake.body[0].x = 1;
	snake.body[0].y = 1;
	snake.movement = EAST;
	snake.alive = true;
	snake.size = 1;
	
	snake.max_size = 10;
	snake.moves_since_last_shortcut = 0;
	

	rabbit rabbit;
	rabbit.p.x = rand() % WIDTH_COUNT; rabbit.p.y = rand() % HEIGHT_COUNT;
	rabbit.alive = true;
	bool quit = false;


	AI ai;
	if (!(ai.active = AI_start(&ai, HEIGHT_COUNT, WIDTH_COUNT)))
		quit = true;


	 if (!(ai.hamilton_cycle = AI_gen_hamilton(&ai)))
			quit = true;

	SDL_RenderClear(my_renderer);
	SDL_Delay(100);
	SDL_RenderPresent(my_renderer);



	while (!quit)
	{
		SDL_SetRenderDrawColor(my_renderer, 0, 0, 0, 255);
		SDL_RenderClear(my_renderer);
		

		SDL_SetRenderDrawColor(my_renderer, 255, 255, 255, 255);
		for (int row = 0; row < HEIGHT_COUNT; row++)
		{
			for (int col = 0; col < WIDTH_COUNT; col++)
			{
				SDL_RenderFillRect(my_renderer, &SCREEN[row][col]);
			}
		}

		//snake_update(&snake);
		game_logic(&snake, &rabbit);
		
		
		
		if (!snake.alive)
			reset(&snake, &rabbit);

	

		input(&snake, &quit);
		AI_make_move(&snake, &ai,&rabbit);

	


		SDL_RenderPresent(my_renderer);
		SDL_Delay(50);
		
	}

	//AI_exit(&ai);
	if (snake.body != NULL)
		free(snake.body);
		snake.body = NULL;
		snake.size = 0;

}


int main(int argc, char* argv[])
{
	if (init())
	{

		SCREEN[0][0].x = 0;
		SCREEN[0][0].y = 0;
		uint8_t width = PIXEL_SIZE;
		SCREEN[0][0].w = SCREEN[0][0].h = width;

		for (int i = 1; i < WIDTH_COUNT; i++)
		{
			SCREEN[0][i].x = SCREEN[0][i - 1].x + width;
			SCREEN[0][i].y = SCREEN[0][i - 1].y;
			SCREEN[0][i].w = SCREEN[0][i].h = width;
		}

		for (int i = 1; i < HEIGHT_COUNT; i++)
		{
			for (int j = 0; j < WIDTH_COUNT; j++)
			{
				if (j == 0)
				{
					SCREEN[i][j].x = SCREEN[i - 1][j].x;
					SCREEN[i][j].y = SCREEN[i - 1][j].y + width;

				}
				else
				{
					SCREEN[i][j].x = SCREEN[i][j - 1].x + width;
					SCREEN[i][j].y = SCREEN[i][j - 1].y;
				}
				SCREEN[i][j].w = SCREEN[i][j].h = width;
			}
		}

		SDL_RenderClear(my_renderer);


		SDL_RenderPresent(my_renderer);


		Game();
	}
	sdl_close();
	return 0;
}