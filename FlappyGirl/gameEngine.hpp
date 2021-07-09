#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include <iostream>
#include "audioManager.h"
#include "textureManager.hpp"
#include <vector>
class gameEngine
{
private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	//gameLogic gameLogic;
	SDL_Event e;

	int r=0, g=0, b=0;

	Uint32 elapsedTime;
	Uint32 lastEvent=0;

	int game_state=0;


	bool init();
	bool loadData();
	void gameloop();

	bool windowShouldClose;
	 int screenHeight;
	 int screenWidth;
	std::string title;

	void menu();
	void Game();

	std::vector<SDL_Cursor*> cursors;

public:
	gameEngine(std::string title, int Width, int Height);
	audioManager audioManager;
	textureManager textureManager;
	SDL_Event* getEventHandler();
	void run();
	void inputHandling();
	void render();
	void clear();


	SDL_Cursor* getCursor(Uint8 index);


	bool rectCollision(SDL_Rect* A, SDL_Rect* B);
	bool mouseCollision(SDL_Rect* A);

	void shouldWindowClose(bool state);

	void change_gameState(int state);
	void setRenderColor(int r,int g,int b);
	 int getScreenW();
	 int getScreenH();
	SDL_Renderer* getRenderer();
	Uint32 getElapsedTime();
	void exit();
};
