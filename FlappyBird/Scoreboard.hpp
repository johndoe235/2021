#pragma once
#include <SDL.H>
#include <vector>
#include <iostream>
#include <stack>
class Scoreboard
{
public:
	Scoreboard(SDL_Texture* texture, SDL_Renderer*,int ScreenW,int ScreenH);
	void render();
	
	void checkScore(SDL_Rect* bird, SDL_Rect* Pipe,int pipeNumber);
	void reset();
	


private:
	SDL_Rect source;
	SDL_Texture* texture;
	SDL_Renderer* renderer;
	SDL_Rect dest;
	int coordinates[10][4]
	{
		{0,0,75,96},      //0
		{75,0,50,96},     //1
		{128,0,75,96},    //2
		{203,0,75,96},    //3
		{278,0,75,96},    //4
		{354,0,75,96},    //5
		{429,0,75,96},    //6
		{503,0,75,96},    //7
		{579,0,75,96},    //8
		{0,97,75,96}      //9


	};
	int score[4]= { -1,-1,-1,0 };
	int size, rectSize;
	int ScreenWidth, ScreenHeight;
	SDL_Rect getNumberRect(int number);
	void getScoreRects(std::stack<SDL_Rect>*stack);
	void addToScore();
	void addPoint();
};