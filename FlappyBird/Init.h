#pragma once
#include <SDL.h>
#include <SDL_image.h> 
#include <iostream>




bool SDLimageInitialize()
{
	bool success = true;
	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		success = false;
		std::cout << "Error in Loading SDL_image!" << SDL_GetError() << std::endl;
	}

	return success;
}
SDL_Texture* createTexture(std::string X,SDL_Renderer* renderer)
{
	SDL_Surface* loadImage = IMG_Load(X.c_str());
	if (loadImage == NULL) {
		std::cout << "Error Surface cannot be loaded:   " << SDL_GetError() << std::endl;
		return NULL;
	}
	
	SDL_Texture* Return_Texture=SDL_CreateTextureFromSurface(renderer, loadImage);
	
	
	if (Return_Texture == NULL)
		std::cout << "Cannot create Texture from surface!" << SDL_GetError()<<std::endl;
	SDL_FreeSurface(loadImage);
		return Return_Texture;
	
}





