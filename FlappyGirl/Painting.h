#pragma once
#include <SDL.h>
class Painting
{

public:
	 void update(SDL_Renderer* renderer);
	 Painting(SDL_Texture* texture, int x, int y, int w, int h, int speed,int id);
	 Painting();


	 void render(SDL_Renderer* renderer);
	 void changeTexture(SDL_Texture* newTexture,int newID);
	 void changeTexture(SDL_Texture* newTexture);
	 int getTextureID();
	 SDL_Rect getDest();
	 int getX();
	 void setX(int newX);
	 void setY(int newY);
	 int getW();
	 int getY();
	 int getH();
	 void move();
	 int getID();
	 void changeSpeed(int newSpeed);
private:
	SDL_Texture* texture;
	int textureID;
	int ID;
	SDL_Rect dest;
	int speed;

	
	
	
};