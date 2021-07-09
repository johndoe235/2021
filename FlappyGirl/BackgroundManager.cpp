#pragma once
#include "BackgroundManager.hpp"
#include "TextureManager.hpp"
#include <sstream>
void BackGroundManager::render(SDL_Renderer* renderer)
{

	for (int i = 0; i < 2; i++)
	{
		//////if (!isRectDisplayed(&dest[i]) )
		//{
			SDL_RenderCopy(renderer, background[i],NULL,&dest[i]);
		//}
	}
}

BackGroundManager::BackGroundManager(int ScreenHeight, int ScreenWidth, textureManager& manager,Uint8 b_count)
	: ScreenWidth(ScreenWidth),ScreenHeight(ScreenHeight),b_count(b_count)
{
	speed = 2;
	setRandomTexture(manager, 0);
	setRandomTexture(manager, 1);

	SDL_QueryTexture(background[0], NULL, NULL, &TextureWidth, &TextureHeight);
	if (SDL_GetDisplayBounds(0, &dest[0]) != 0)
		std::cout << SDL_GetError() << std::endl;

	dest[1] = { dest[0].x+dest[0].w,dest[0].y,dest[0].w,dest[0].h };
	///source[0] = { 0,0,TextureWidth/2,TextureHeight};
	//source[1] = { TextureWidth / 2, 0 , TextureWidth / 2, TextureHeight };


	//source[0] = { 0,0,TextureWidth ,TextureHeight };
	//source[1]= { 0,0,TextureWidth ,TextureHeight };

	


}

void BackGroundManager::update(SDL_Renderer* renderer, textureManager& manager)
{
	if(background[1]==background[0])
			if( dest[1].x > dest[0].x)
			setRandomTexture(manager, 1);
		else
			setRandomTexture(manager, 0);

		dest[0].x-=speed;
		dest[1].x-=speed;
		if (dest[0].x + dest[0].w < 0)
		{
			dest[0].x = dest[1].x + dest[1].w;
			setRandomTexture(manager, 0);
		}
		 if (dest[1].x + dest[1].w < 0)
		{
			dest[1].x = dest[0].x + dest[0].w;
			setRandomTexture(manager,1);
		}
	
	render(renderer);



}

bool BackGroundManager::isRectDisplayed(SDL_Rect* rectangle)
{
	if ( (rectangle->x + rectangle->w)<0 || (rectangle->x + rectangle->w) >ScreenWidth)
		return false;
	
	return true;
}

void BackGroundManager::setRandomTexture(textureManager& tmanager,int dest)
{


	std::string name = "background";
	srand(SDL_GetPerformanceCounter());
	int lucky = rand() % b_count + 1;
	std::stringstream ss;
	ss << lucky;
	name.append(ss.str());

	background[dest]=tmanager.getAsset(name);

}


