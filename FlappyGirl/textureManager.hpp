#pragma once
#include <SDL_image.h>
#include <iostream>
#include <SDL.h>
#include <map>


class textureManager
{
public:
	textureManager();
	bool init();
	bool loadAssets(std::string filepaths[],std::string texturenames[], int count,SDL_Renderer* renderer);

	bool loadAsset(std::string filepath,SDL_Renderer* renderer);
	void exit();
	
	SDL_Texture* getAsset(std::string name);

private:
	SDL_Renderer* renderer;
	std::map<std::string,SDL_Texture*> textures_map;
	SDL_Texture* createTexture(std::string X,SDL_Renderer* renderer);

};