#pragma once
#include <SDL.h>
#include <vector>
//#include "scoreboard.h"
#include "Painting.h"
#include "Flapina.hpp"
#include "TextureManager.hpp"
#include "audioManager.h"
class Paintings
{
public:
	Paintings(SDL_Renderer* renderer, /*SDL_Texture* scoreboardTexture,*/ textureManager* manager, int screen_width,int screen_height,int count);
	void update(SDL_Renderer* renderer, Flapina* protagonist, textureManager* manager/* audioManager* audiomanager*/);
	//int update(SDL_Renderer* renderer,Flapina* protagonist,textureManager* manager);
	void deathUpdate(SDL_Renderer* renderer, textureManager& textureManager);
	std::vector<Painting>& getList();

	bool Collision(SDL_Rect* A);

private:
	int p_count;
	int ScreenWidth;
	int ScreenHeight;
	int gap;
	std::vector<Painting> paintings;
	std::vector<bool> isTextureTaken;
	//Scoreboard scoreboard;


	bool collision(SDL_Rect* A,SDL_Rect* B);
	



	std::string getRandomTexture();
	

};