#include "gObject.hpp"


void Object::render()
{
	if (texture != NULL)
		SDL_RenderCopy(renderer, texture, NULL, &dest);
	else
	{
		SDL_SetRenderDrawColor(renderer,r, g, b, 255);
		SDL_RenderFillRect(renderer, &dest);
	}
		
		
}
void Object::changeRGB(int r, int g, int b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}




int Object::getH()
{
	return this->dest.h;
}



