#include "Painting.h"

void Painting::update(SDL_Renderer* renderer)
{
	render(renderer);
}

/*Painting::Painting(SDL_Texture* texture, int x, int y, int w, int h,int speed,int TextureID)
{
	this->texture = texture;
	this->dest = { x,y,w,h };
	this->speed = speed;
	this->textureID = TextureID;
}
*/

Painting::Painting(SDL_Texture* texture, int x, int y, int w, int h, int speed, int ID)
{
	this->texture = texture;
	this->dest = { x,y,w,h };
	this->speed = speed;
	this->ID = ID;
	this->textureID = -1;
}

Painting::Painting()
{

}


void Painting::changeTexture(SDL_Texture* newTexture, int newID)
{
	this->texture = newTexture;
	this->textureID = newID;
}

void Painting::changeTexture(SDL_Texture* newTexture)
{
	this->texture = newTexture;
}

int Painting::getTextureID()
{
	return this->textureID;
}

SDL_Rect Painting::getDest()
{
	return this->dest;
}

int Painting::getX()
{
	return this->dest.x;
}

void Painting::setX(int newX)
{
	this->dest.x = newX;
}

void Painting::setY(int newY)
{
	this->dest.y = newY;
}

int Painting::getW()
{
	return this->dest.w;
}

int Painting::getY()
{
	return this->dest.y;
}

int Painting::getH()
{
	return dest.h;
}

void Painting::move()
{
	this->dest.x -= speed;
}

int Painting::getID()
{
	return this->ID;
}

void Painting::changeSpeed(int newSpeed)
{
	this->speed = newSpeed;
}

void Painting::render(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, texture, NULL, &dest);

}
