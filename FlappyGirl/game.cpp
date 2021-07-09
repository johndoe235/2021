#pragma once
#include "gameEngine.hpp"
#include "Flapina.hpp"
#include "Pixie.hpp"
#include "BackgroundManager.hpp"
#include "scoreboard.h"
#include "Paintings.h"

void OnDeath(Flapina& Flapina,Pixie& pixie, Paintings& paintings, gameEngine* engine, BackGroundManager& manager,Scoreboard& scoreboard)
{
	SDL_Rect flapina = Flapina.getRect();
	SDL_Rect nani = { -1,-1,-1 };
	double ANGLE = 0;

	engine->audioManager.playChunk("death_sound");

	engine->change_gameState(0);
	SDL_Event* holder = engine->getEventHandler();


	while (nani.y < engine->getScreenH())
	{
		flapina.y += 5;


		manager.render(engine->getRenderer());
		
		
		paintings.deathUpdate(engine->getRenderer(), engine->textureManager);
		pixie.onDeathUpdate(engine->getRenderer(), &flapina, 3);
		scoreboard.onDeathUpdate(engine->getRenderer());

		SDL_RenderCopyEx(engine->getRenderer(), engine->textureManager.getAsset("protagonist"), NULL, &flapina, ANGLE -= 5, NULL, SDL_FLIP_NONE);
		SDL_RenderCopy(engine->getRenderer(), engine->textureManager.getAsset("ex_mark"), NULL, &nani);

		engine->render();

		nani = pixie.getRect();
		nani.y -= pixie.getRect().w-10;


			while (SDL_PollEvent(holder) != 0)
			{
				if (holder->type == SDL_QUIT)
				{
					engine->shouldWindowClose(true);
					return;
				}
				else if (holder->type == SDL_KEYDOWN)
				{
					if (holder->key.keysym.sym==SDLK_ESCAPE)
					{
						engine->shouldWindowClose(true);
						return;
					}
					else if (holder->key.keysym.sym == SDLK_SPACE)
					{
						engine->change_gameState(1);
						
					}
				}
			}
	}
	

	
	
	

}


void gameEngine::menu()
{
	SDL_ShowCursor(1);
	SDL_SetCursor(cursors[0]);
	//menu items
	//background
	SDL_Rect play; //play button
	SDL_Rect title;	//title
	SDL_Rect protag;
	bool toggle;
	Uint8 alpha;
	SDL_GetTextureAlphaMod(textureManager.getAsset("play_button"), &alpha);
	toggle = false;
	Uint32 lastEvent = SDL_GetTicks()/1000;
	
	
	title.w = (int)( screenWidth / 1.5);

	title = { (int)(screenWidth * 0.10) ,  (int)(screenHeight * 0.1), title.w, screenHeight/4 };

	play.w = (int)(screenWidth * 0.1);
	play.x = screenWidth / 2 - play.w / 2;
	play.y= screenHeight/2 + (int)(screenHeight/2* 0.16);
	play.h = play.w/2;
	
	protag = { title.x + title.w-100,title.y + title.h-100, (int)(screenWidth * 0.4), (int)(screenWidth * 0.6) };
	
	
	
	//audioManager.playMusic("title_music");
	while (game_state == 0)
	{
		this->clear();
		
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				windowShouldClose = true;
				return;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_ESCAPE)
				{
					windowShouldClose = true;
					return;
				}
				else if (e.key.keysym.sym == SDLK_SPACE)
				{
					game_state = 1;
				}
			}
				else if (e.type == SDL_MOUSEBUTTONDOWN)
				{
					if (mouseCollision(&play))
					{
						game_state = 1;
					}
				}
				else if(e.type==SDL_MOUSEMOTION)
						if ((mouseCollision(&play)))
						{
							play.w = (int)(screenWidth * 0.1)+10;
							play.h = play.w / 2;
							SDL_SetCursor(cursors[1]);
						}
						else
						{
							play.w = (int)(screenWidth * 0.1);
							play.h = play.w / 2;
							SDL_SetCursor(cursors[0]);
						}

		}
		
			if (toggle)
				SDL_SetTextureAlphaMod(textureManager.getAsset("play_button"), alpha+=5);
			else
				SDL_SetTextureAlphaMod(textureManager.getAsset("play_button"), alpha-=5);

			if (alpha >= 250)
				toggle = false;
			if (alpha <= 20)
				toggle = true;
		

		
		
		SDL_RenderCopy(renderer, textureManager.getAsset("background"), NULL, NULL);
		SDL_RenderCopyEx(renderer, textureManager.getAsset("protagonist"), NULL, &protag, 0, NULL, SDL_FLIP_HORIZONTAL);
		SDL_RenderCopy(renderer, textureManager.getAsset("title"), NULL, &title);
		SDL_RenderCopy(renderer, textureManager.getAsset("play_button"), NULL, &play);
	//	SDL_RenderCopy(renderer, textureManager.getAsset("protagonist"), NULL, &protag);
		
		this->render();
	}

}

void gameEngine::Game()
{
	SDL_ShowCursor(0);
	Flapina protagonist(textureManager.getAsset("protagonist"),screenWidth,screenHeight);
	Pixie sansa(textureManager.getAsset("sansa"), textureManager.getAsset("sansa_wings"), &protagonist);

	
	BackGroundManager backgroundmaster(getScreenW(), getScreenH(),textureManager,7 );
	Scoreboard scoreboard(textureManager.getAsset("score_texture"), this->screenWidth, this->screenHeight);
	Paintings paintings(this->renderer,&textureManager, screenWidth, screenHeight,18);

	
	while (game_state == 1)
	{
	


		this->clear();

					while (SDL_PollEvent(&e) != 0)
					{
						if (e.type == SDL_QUIT)
						{
							windowShouldClose = true;
							return;
						}
						else if (e.type == SDL_KEYDOWN)
						{
							if (e.key.keysym.sym == SDLK_ESCAPE)
							{
								windowShouldClose = true;
								return;
							}
							else if (e.key.keysym.sym == SDLK_SPACE)
							{
								protagonist.move(elapsedTime);
								
								//audioManager.playChunk("jump_sound");
							}

						}
					}
		//SDL_RenderCopy(renderer, textureManager.getAsset("background"), NULL, NULL);


		backgroundmaster.update(renderer, textureManager);
		
		protagonist.update(renderer);
		paintings.update(renderer, &protagonist, &textureManager);
		sansa.update(renderer, elapsedTime);
		if ( paintings.Collision(&protagonist.getHitbox()) )
		{
			OnDeath(protagonist, sansa,paintings,this,backgroundmaster,scoreboard);
			return;
		}

		if (protagonist.getY() + protagonist.getH()+10 < 0)
		{
			
			audioManager.playChunk("thunder_sound");
			OnDeath(protagonist, sansa, paintings, this, backgroundmaster, scoreboard);
			return;
		}

		if (protagonist.getY()-50 > screenHeight)
		{
			OnDeath(protagonist, sansa, paintings, this, backgroundmaster, scoreboard);
			return;
		}

	
		if (scoreboard.update(this->renderer, &protagonist.getRect(), paintings.getList()))
		{
			audioManager.playChunk("point_sound");
			
		}
		


		this->render();
		
	}
}

