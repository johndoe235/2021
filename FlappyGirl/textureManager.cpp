#pragma once
#include "textureManager.hpp"
#include "SDL_image.h"
textureManager::textureManager()
{

}

bool textureManager::init()
{
	return true;
}

bool textureManager::loadAssets(std::string filepaths[], std::string texturenames[],int count, SDL_Renderer* renderer)
{

	for (int i = 0; i < count; i++)
	{
		textures_map.insert(std::pair<std::string, SDL_Texture*>(texturenames[i], createTexture(filepaths[i], renderer)));
		if (textures_map[texturenames[i]] == NULL)
		{
			std::cout << "Map Texture is NULL! " << filepaths << std::endl;
			return false;
		}
	}
	return true;
}

bool textureManager::loadAsset(std::string filepath,SDL_Renderer* renderer)
{
	return true;
}

void textureManager::exit()
{
	std::map<std::string, SDL_Texture*>::iterator it;
	for (it = textures_map.begin(); it != textures_map.end(); ++it)
		SDL_DestroyTexture(it->second);

	textures_map.clear();
}

SDL_Texture* textureManager::getAsset(std::string name)
{
	if (textures_map.find(name) == textures_map.end())
	{

		std::cout << "invalid texture name " << name << std::endl;
		return NULL;
	}
	else
		return textures_map[name];

}

SDL_Texture* textureManager::createTexture(std::string X,SDL_Renderer* renderer)
{

	SDL_Surface* temp = IMG_Load(X.c_str());
	if (temp == NULL)
	{
		std::cout << "Cannot find " << X << " SDL Error:" << IMG_GetError()<<std::endl;
	}
	SDL_Texture* newTexture = SDL_CreateTextureFromSurface(renderer, temp);

	if (newTexture == NULL)
		std::cout << "Cannot create Texture " << X << " SDL Error:" << IMG_GetError() << std::endl;

	return newTexture;
}
