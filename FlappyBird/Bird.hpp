#pragma once
#include "gObject.hpp"
class Bird:public Object 
{
public:
	Bird(SDL_Texture* texture, SDL_Renderer* r);
	Bird(SDL_Texture* texture, SDL_Renderer* renderer, SDL_Rect dest);
	Bird();
	
	void jump();
	void gravity();
	int getY();
	void render();
	void reset();
	SDL_Rect& getDestRect();
	
private:
	float speed;
};