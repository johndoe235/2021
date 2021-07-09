#include "background.hpp"

Background::Background(SDL_Texture* texture, SDL_Renderer* renderer,int ScreenW,int ScreenH)
	:ScreenWidth(ScreenW),ScreenHeight(ScreenH)
{
	this->texture = texture;
	this->renderer = renderer;
	
	
	int w, h,access;
	Uint32 format;
	SDL_QueryTexture(texture, &format, &access, &w, &h);
	this->source = { 0,30,ScreenW,h };
	this->source2 = { ScreenWidth,30,w,h };
	DEST.push_back({ 0,0,ScreenW,ScreenH });
	DEST.push_back({ ScreenW,0,ScreenW,ScreenH });
	float speed = 0.001f;
	std::cout << ScreenW << " " << ScreenH << std::endl;
}

void Background::render()
{
	
	
		SDL_RenderCopy(this->renderer, this->texture, &this->source, &this->DEST[0]);
		
	
	
	
		SDL_RenderCopy(this->renderer, this->texture, &this->source2, &this->DEST[1]);

	if (DEST[0].x + DEST[0].w <= 0)
		DEST[0].x = this->ScreenWidth;

	if (DEST[1].x + DEST[1].w < 0)
		DEST[1].x = DEST[0].x + DEST[0].w;

}

void Background::move()
{
	this->DEST[0].x -= 5;
	this->DEST[1].x -= 5;
}

void Background::reset()
{
	DEST.clear();
	DEST.push_back({ 0,0,ScreenWidth,ScreenHeight });
	DEST.push_back({ ScreenWidth,0,ScreenWidth,ScreenHeight });
}
