#include <SDL.h>
#include <iostream>
#include "Window.hpp"
#include "Bird.hpp"
#include <vector>
#include "Pipe.hpp"
#include "Init.h"
#include "background.hpp"
#include "Scoreboard.hpp"
#define GAP 190
#define FPS 60
#define FRAME_DELAY 1000/FPS

bool quit = false;
int state;
SDL_Texture* Textures[4];

std::vector<Pipe> pipes;


int getRandomY(int Screenheight)
{
	srand(SDL_GetTicks());
	int randomNumber = rand() % Screenheight;
	if (randomNumber >= Screenheight - 100)
		return randomNumber - 100;
	if (randomNumber < Screenheight / 2-200)
		return randomNumber + 300;

	return randomNumber;

}
int getY_Adjusted(int Y, int ScreenHeight)
{
	std::cout << Y << std::endl;
	srand(SDL_GetTicks());
	int randomNum = rand() % 3;
	
	
	if (Y + 100 > ScreenHeight)
		return Y - 100;
	switch (randomNum)
	{
	case 1:
		return Y+50;
	case 2:
		return Y + 68;
	case 3:
			return Y - 50;
	case 4:
			return Y - 45;
	default:
		return Y;
	}
}


void Game(Window& window,SDL_Event& e,Bird& bird,Background &background,Scoreboard &scoreboard)
{
	
	
	pipes.push_back(Pipe(Textures[1], window.getRenderer(), {window.getW(),(int)window.getH()*1/2,150,(int)window.getH()-window.getH() *1/2}));
	pipes.push_back(Pipe(Textures[1], window.getRenderer(), { window.getW(),0,150,150}));
	pipes.push_back(Pipe(Textures[1], window.getRenderer(), { window.getW()+GAP+150,(int)window.getH() * 1 / 2,150,(int)window.getH() - window.getH() * 1 / 2 }));
	pipes.push_back(Pipe(Textures[1], window.getRenderer(), { window.getW() + GAP + 150,0,150,150 }));
	pipes.push_back(Pipe(Textures[1], window.getRenderer(), { window.getW() + 2*GAP + 2*150,(int)window.getH() * 1 / 2,150,(int)window.getH() - window.getH() * 1 / 2 }));
	pipes.push_back(Pipe(Textures[1], window.getRenderer(), { window.getW() + 2*GAP + 2*150,0,150,150 }));
	pipes.push_back(Pipe(Textures[1], window.getRenderer(), { window.getW() + 3*GAP + 3*150,(int)window.getH() * 1 / 2,150,(int)window.getH() - window.getH() * 1 / 2 }));
	pipes.push_back(Pipe(Textures[1], window.getRenderer(), { window.getW() + 3*GAP + 3*150,0,150,150 }));

	Uint32 frameStart;
	int frameTime;
	while (!quit)
	{
		frameStart = SDL_GetTicks();




		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
				quit = true;
			else if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_SPACE)
				{
					if(state == 1)
					bird.jump();
				}
			}
		}




		window.Clear();
		background.render();
		for (int i = 0; i < pipes.size(); i++)
		{
			if(state==1)
			pipes[i].move();
			if (pipes[i].getPosX() < window.getW())
				if(i%2==0)
					pipes[i].render(false);
				else
				pipes[i].render(true);




			if (pipes[i].getPosX() + pipes[i].getW() < 0)
			{
				srand(SDL_GetTicks());
				if (i == 0)
				{
					
					pipes[i].setX(pipes[pipes.size() - 1].getPosX()+150 + GAP);
					pipes[i].setY(getY_Adjusted(pipes[pipes.size()-2].getY(), window.getH()));
					pipes[i].setH(window.getW() - pipes[i].getY());
				}
				else if (i % 2 != 0)
				{
					pipes[i].setX(pipes[i - 1].getPosX());
					pipes[i].setH(pipes[i - 1].getY()-2*bird.getH()-5 );
				}
				else
				{
					pipes[i].setX(pipes[i - 2].getPosX() + GAP+pipes[i].getW());
					pipes[i].setY(getY_Adjusted(pipes[i - 2].getY(), window.getH()));
					pipes[i].setH(window.getW() - pipes[i].getY()-bird.getH());
				}
			}
			if (state == 1 && i%2!=0)
				scoreboard.checkScore(&bird.getDestRect(), pipes[i].getDestRect(),i);

			if (pipes[i].collision(&bird.getDestRect()))
			{
				state = 2;

			}
			


		}
	
		bird.gravity();
		if (bird.getY() >window.getH())
			return;
		scoreboard.render();
		bird.render();
		background.move();
		window.Present();
		frameTime = SDL_GetTicks() - frameStart;

		if (FRAME_DELAY > frameTime)
			SDL_Delay(FRAME_DELAY - frameTime);
		
	}


}


int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0 && IMG_Init(IMG_INIT_PNG)>0)
		std::cout << "Cannot initialize SDL! " << SDL_GetError() << std::endl;
	else 
	{
		SDL_Event e;
		
		Window window("Flappy Bird", 860, 640);
		
		Textures[0] = createTexture("birdsheet.png",window.getRenderer());
		Textures[1] = createTexture("pipe.png", window.getRenderer());
		Textures[2] = createTexture("skyBig.png", window.getRenderer());
		Textures[3] = createTexture("numbers1.png", window.getRenderer());
		Bird bird(Textures[0], window.getRenderer());
		Scoreboard scoreboard(Textures[3],window.getRenderer(),window.getW(),window.getH());
		Background zackground(Textures[2],window.getRenderer(),window.getW(),window.getH());
	
		
		state = 1;
		while (!quit)
		{
			Game(window,e,bird,zackground,scoreboard);
			state = 1;
			bird.getDestRect() = SDL_Rect{ 20,20,80,60 };
			window.Clear();
			window.Present();
			pipes.clear();
			bird.reset();
			zackground.reset();
			scoreboard.reset();
		
		}
		IMG_Quit();
		window.DestroyWindow();
		for (int i = 0; i < 4; i++)
			SDL_DestroyTexture(Textures[i]);

		SDL_Quit();
		
	}
    return 0;
}



