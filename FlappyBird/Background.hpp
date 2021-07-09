#pragma once
#include "gObject.hpp"
#include <vector>

class Background : public Object
{
public:
	Background(SDL_Texture* texture, SDL_Renderer* renderer, int ScreenW, int ScreenH);
	void render();
	void move();
	void reset();

private:
	std::vector<SDL_Rect> DEST;
	SDL_Rect source2;
	int ScreenWidth;
	int ScreenHeight;

};