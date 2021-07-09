#pragma once
#include <SDL.h>
#include "TextureManager.hpp"
class BackGroundManager
{
private:
	SDL_Rect dest[2];
	SDL_Rect source[2];
	SDL_Texture* background[2];

	int ScreenHeight;
	int ScreenWidth;
	int TextureHeight;
	int TextureWidth;

	Uint8 b_count;
	int speed;

	void render();
public:
	void render(SDL_Renderer* renderer);

	BackGroundManager(int ScreenHeight, int ScreenWidth, textureManager& manager, Uint8 b_count);

	BackGroundManager(int ScreenHeight, int ScreenWidth, SDL_Texture* starting_texture,Uint8 b_count);
	void update(SDL_Renderer* renderer);
	void update(SDL_Renderer* renderer, textureManager& manager);
	bool isRectDisplayed(SDL_Rect* rectangle);
	void setRandomTexture(textureManager& tmanager, int dest);
	//void setRandomTexture(textureManager& tmanager);
	//void setRandomTexture(textureManager tmanager);


};
