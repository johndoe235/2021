#pragma once
#include <SDL.h>

class Flapina
{
public:
	
	Flapina(SDL_Texture* texture, int ScreenWidth, int screenHeight);
	void move(Uint32 elapsedTime);
	void update(SDL_Renderer* render);
	int getX();
	int getY();
	int getW();
	int getH();
	SDL_Rect getRect();
	SDL_Rect getHitbox();
private:
	
	SDL_Rect dest;
	SDL_Rect hit_box;
	SDL_Texture* texture;
	float speed;
	float vel_Y;
	int W, H;
	Uint32 jump_time;
	
	void render(SDL_Renderer* render);
	void gravity();

	

	
	
};