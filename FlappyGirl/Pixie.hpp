#pragma once
#include <SDL.h>
#include "Flapina.hpp"
class Pixie
{
private:
	SDL_Rect wings_source;
	SDL_Rect frontwing_dest;
	SDL_Rect backwing_dest;
	SDL_Rect dest;
	SDL_Rect hit_box;
	SDL_Texture* texture;
	SDL_Texture* wing;
	Flapina* master;
	Uint32 last_Frame;
	int frame_number;

	void render(SDL_Renderer* renderer);
public:
	Pixie(SDL_Texture* texture, SDL_Texture* wings, Flapina* master);
	void onDeathUpdate(SDL_Renderer* renderer, SDL_Rect* Flapina ,int speed);
	void onDeathUpdate(SDL_Renderer* renderer, SDL_Rect* Flapina);
	void update(SDL_Renderer* renderer,Uint32 ElapsedTime);
	SDL_Rect getRect();
};

