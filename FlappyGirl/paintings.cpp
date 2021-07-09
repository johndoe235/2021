#include "paintings.h"
#include <iostream>
#include "audioManager.h"
#include <sstream>

/*
Paintings::Paintings(SDL_Renderer* renderer, SDL_Texture* scoreboardTexture,textureManager* manager, int screen_width, int screen_height, int count)
{
	this->scoreboard =* new Scoreboard(scoreboardTexture, screen_width, screen_height);
	this->ScreenWidth = screen_width;
	this->gap =  ScreenWidth/5;
	this->p_count = count;

	int x=ScreenWidth, y= screen_height / 2 +100, h=400, w=300, speed=3, ID=0;
	Painting p(manager->getAsset("p1"),x,y,w,h,speed,0);
	paintings.push_back(p);
	std::string texturename = "p2";

	isTextureTaken[0] = true;
	isTextureTaken[1] = true;
	


	isTextureTaken.resize(count + 1);
	for (int i = 1; i < 8; i++)
	{
		paintings.push_back(*new  Painting(manager->getAsset(texturename), paintings[i-1].getX()+gap+w, y, w, h, speed, i));
		texturename[1] = i + '0';
		isTextureTaken[i] = true;
	}

	

}

void Paintings::update(SDL_Renderer* renderer, Flapina* protagonist, textureManager* manager,audioManager* audiomanager)
{
	int returned = 0;
	for (int i = 0; i < 8; i++)
	{
		paintings[i].move();
		
		if (paintings[i].getX()<ScreenWidth)
		{
			paintings[i].render(renderer);
		}
			if (collision(&protagonist->getRect(), &paintings[i].getDest()))
			{
				returned= 666;
			}
			///put  paintings,reincarnation
		if (paintings[i].getX() + paintings[i].getW() < 0)
		{
			if (i == 0)
			{
				paintings[i].setX(paintings[paintings.size() - 1].getX() + paintings[paintings.size() - 1].getW() + gap);
				
			}
			else
				paintings[i].setX(paintings[i-1].getX() + paintings[i-1].getW() + gap);

			paintings[i].changeTexture(manager->getAsset(getRandomTexture()), 2);
		}

	//	if (scoreboard.checkScore(&protagonist->getRect(), &paintings[i].getDest(), i))
		//{
		
		//	audiomanager->playChunk("point_sound");
		//}
	}


	//scoreboard.render(renderer);
	
	

}
*/

Paintings::Paintings(SDL_Renderer* renderer, textureManager* manager, int screen_width, int screen_height, int count)
{
	this->ScreenWidth = screen_width;
	this->ScreenHeight = screen_height;
	this->gap = ScreenWidth / 5;
	this->p_count = count;

	
	//initialize 8 paintings 4 on the botton of the screen 4 on top of the screen each with a unique texture
	int x = ScreenWidth, y = (int)screen_height*0.6, h = 350, w = 250, speed = 7, ID = 0;
	paintings.push_back(Painting(manager->getAsset("p1"), x, y, w, h, speed, 0));
	//paintings.push_back(Painting(manager->getAsset("p2"), x, 0, w, h-(int)screen_height*0.4, speed, 1));
	std::string texture = "pX";
	for (int i = 1; i < 4; i++)
	{
		texture[1] = i + '0'+1;

		//paintings[i] = *new  Painting(manager->getAsset(texture), paintings[i - 1].getX() + gap + w, y, w, h, speed, i);
		if(i%2==0)
		paintings.push_back(Painting(manager->getAsset(texture), paintings[i - 1].getX() + gap + w, y, w, h, speed, i));
		else
			paintings.push_back(Painting(manager->getAsset(texture), paintings[i - 1].getX() + gap + w, 0, w, h, speed, i));
	}



}

void Paintings::update(SDL_Renderer* renderer, Flapina* protagonist, textureManager* manager )
{
	for (int i = 0; i < paintings.size(); i++)
	{
		paintings[i].move();

		if (paintings[i].getX() < ScreenWidth)
		{
			paintings[i].render(renderer);
		}

		///put  paintings,reincarnation
		if (paintings[i].getX() + paintings[i].getW() < 0)
		{
			if (i == 0)
			{
				paintings[i].setX(paintings[paintings.size() - 1].getX() + paintings[paintings.size() - 1].getW() + gap);

			}
			else
				paintings[i].setX(paintings[i - 1].getX() + paintings[i - 1].getW() + gap);
			

			if(protagonist->getY()+protagonist->getH()<=ScreenHeight)
				paintings[i].setY(protagonist->getY());
			else
				paintings[i].setY(protagonist->getY()-paintings[i].getH());

			
			

			paintings[i].changeTexture(manager->getAsset(getRandomTexture()));
		}

	}
}

void Paintings::deathUpdate(SDL_Renderer* renderer, textureManager& textureManager)
{
	for (Painting& painting : paintings)
	{
		painting.render(renderer);
	}
}

std::vector<Painting>& Paintings::getList()
{
	return paintings;
}

bool Paintings::Collision(SDL_Rect* A)
{
	for (Painting& painting : paintings)
	{
		if (collision(A, &painting.getDest()))
			return true;
	}
	return false;
}

bool Paintings::collision(SDL_Rect* A, SDL_Rect* B)
{
	if (A->x + A->w < B->x || B->x + B->w - 5 < A->x)
		return false;
	if (A->y + A->h - 2 < B->y || B->y + B->h - 5 < A->y)
		return false;

	return true;
}

std::string Paintings::getRandomTexture()
{
	std::string name = "p";
	srand(SDL_GetTicks()/100);
	
	std::stringstream ss;
	ss << rand() % p_count + 1;;
	name.append(ss.str());
	

	return name;
}
