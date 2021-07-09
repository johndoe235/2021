#include "Flapina.hpp"



Flapina::Flapina(SDL_Texture* texture, int ScreenWidth, int screenHeight)
	:texture(texture)
{
	
	speed = 0;
	dest.x =130;
	dest.y =200;
	W=static_cast<int>(ScreenWidth*0.08);
	H = static_cast<int>(ScreenWidth * 0.15);
	dest.w = W;
	dest.h = H;
	hit_box.w = dest.w - 10;
	hit_box.x = dest.x + 10;
	hit_box.y = dest.y;
	hit_box.h = dest.h;
}

void Flapina::gravity()
{
	/// 0.725f;
	speed += 0.825f;
	vel_Y = vel_Y + speed;
	this->dest.y = vel_Y;

	this->hit_box.w = dest.w - 32;
	this->hit_box.x = dest.x + 32;
	this->hit_box.y = dest.y + 20;
	this->hit_box.h = dest.h - 30;
}

void Flapina::move(Uint32 elapsedTime)
{
	//jump has been pressed resize dest's height for 1-2(?) frames
	//if(SDL_GetTicks()-jump_time>200)
	jump_time = SDL_GetTicks();
	//-12.96;
	speed =-14.96;

}

void Flapina::update(SDL_Renderer* renderer)
{
	gravity();
	render(renderer);
}

int Flapina::getX()
{
	return dest.x;
}

int Flapina::getY()
{
	return dest.y;
}

int Flapina::getW()
{
	return dest.w;
}

int Flapina::getH()
{
	return dest.h;
}

SDL_Rect Flapina::getRect()
{
	return dest;
}

SDL_Rect Flapina::getHitbox()
{
	return hit_box;
}

void Flapina::render(SDL_Renderer* renderer)
{
	
	SDL_Rect jump = { dest.x,dest.y,dest.w,dest.h - 40 };
	if(SDL_GetTicks()-jump_time<200)
		SDL_RenderCopy(renderer, texture, NULL, &jump);
	else
	SDL_RenderCopy(renderer, texture, NULL, &dest);






	//TESTING COMMENT OUT
	//SDL_RenderDrawLine(renderer, hit_box.x, hit_box.y, hit_box.x + hit_box.w, hit_box.y);
	//SDL_RenderDrawLine(renderer, hit_box.x, hit_box.y, hit_box.x , hit_box.y+hit_box.h);
	//SDL_RenderDrawLine(renderer, hit_box.x+ hit_box.w,hit_box.y, hit_box.x + hit_box.w, hit_box.y+hit_box.h);
	//SDL_RenderDrawLine(renderer, hit_box.x + hit_box.w, hit_box.y, hit_box.x + hit_box.w, hit_box.y + hit_box.h);
	//SDL_RenderDrawLine(renderer, hit_box.x, hit_box.y + hit_box.h, hit_box.x + hit_box.w, hit_box.y + hit_box.h);
	//SDL_RenderDrawLine(renderer, hit_box.x, hit_box.y, hit_box.x + hit_box.w, hit_box.y + hit_box.h);
	

}



