#include "Pixie.hpp"
#include <iostream>



Pixie::Pixie(SDL_Texture* texture, SDL_Texture* wings, Flapina* masterr)
	:texture(texture),wing(wings)
{
	
	this->master = masterr;
	this->last_Frame = 0;
	this->frame_number = 0;

	wings_source = { 0,0,500,500 };
	
	dest = { master->getX() - master->getW()/2 ,master->getY() + master->getH()/2,static_cast<int>(master->getW() * 0.6),static_cast<int>(master->getW() * 0.6) };
	frontwing_dest = { dest.x - 30,dest.y + 15,dest.w,dest.h };
	backwing_dest = { frontwing_dest.x,frontwing_dest.y - 2,frontwing_dest.w,frontwing_dest.h };


}

void Pixie::onDeathUpdate(SDL_Renderer* renderer, SDL_Rect* Flapina,int speed)
{
	
	if (Flapina->y > dest.y)
		dest.y+=speed;

	frontwing_dest.y = dest.y;
	backwing_dest.y = frontwing_dest.y - 10;

	if (SDL_GetTicks() - last_Frame > 150)
	{

		if (frame_number < 3)
			frame_number++;
		else
			frame_number = 0;
		last_Frame = SDL_GetTicks();
	}
	
	this->render(renderer);
}

void Pixie::render(SDL_Renderer* renderer)
{
	




	

	wings_source.x = frame_number * 500;


	//backwing
	SDL_RenderCopy(renderer, wing, &wings_source, &backwing_dest);

	SDL_RenderCopy(renderer, texture, NULL, &dest);

	//front wing
	SDL_RenderCopy(renderer, wing, &wings_source, &frontwing_dest);
}

void Pixie::update(SDL_Renderer* renderer,Uint32 ElapsedTime)
{
	
	if (master->getY()> dest.y)
		dest.y++;
	else if (master->getY() < dest.y)
		dest.y--;
	frontwing_dest.y = dest.y;

	backwing_dest.y = frontwing_dest.y-10;

	if (SDL_GetTicks()-last_Frame >150)
	{
		
		if (frame_number < 3)
			frame_number++;
		else
			frame_number = 0;
		last_Frame = SDL_GetTicks();
	}

	render(renderer);
	

}

SDL_Rect Pixie::getRect()
{
	return this->dest;
}


