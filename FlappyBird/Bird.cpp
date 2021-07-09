#include "Bird.hpp"

Bird::Bird(SDL_Texture* texture, SDL_Renderer* renderer)
	
{
	this->texture = texture;
	this->renderer = renderer;
	
	this->r = rand() % 255;
	this->g = rand() % 255;
	this->b = rand() % 255;
	this->speed = 0;

	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	this->source = { 17,0,17,12 };
	this->dest = { 20,20,17*5,12*5 };

}

Bird::Bird(SDL_Texture* texture, SDL_Renderer* renderer, SDL_Rect dest)
	
{
	
	this->texture =texture;
	this->renderer = renderer;
	this->dest = dest;
	this->r = rand() % 255;
	this->g = rand() % 255;
	this->b = rand() % 255;
	
	this->speed = 0;
}
void Bird::jump()
{
	this->speed = -4.6f;

}
void Bird::gravity()
{
	

	this->dest.y += speed;
	this->speed += 0.325f;

}

int Bird::getY()
{
	return this->dest.y;
}

void Bird::render()
{
	if (texture != NULL)
	{
		
		
			if (speed < -1.5)
				this->source.x = 0;
			else if (speed < -0.5)
				this->source.x = 17;
			else if(speed<0.3)
				this->source.x = 34;
			else
				this->source.x = 0;
		
		int angle=-10;
		if (this->speed < -1)
			int angle = -25 +1.5*speed;
		if (this->speed >= -0.2 && this->speed<=0.2)
			angle = 0;
		 if (this->speed > 2.0)
			angle = 10+ 2.5 * speed;;
		

			//SDL_RenderCopy(renderer, texture, &source, &dest);
			SDL_RenderCopyEx(renderer, texture, &source, &dest, angle, NULL, SDL_FLIP_NONE);
	}
	else
	{
		SDL_SetRenderDrawColor(renderer, r, g, b, 255);
		SDL_RenderFillRect(renderer, &dest);
	}
}


SDL_Rect& Bird::getDestRect()
{
	return this->dest;
}
void Bird::reset()
{
	this->speed = 0;
}



