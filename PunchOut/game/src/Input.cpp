#include "../include/Game.h"

#include "../../engine/include/Event.h"


#include <SDL_events.h>

#include <iostream>


void Game::handleInput() 
{
	
	static Event event;
  	static bool isUpArrowPressed=false;
	static bool isLeftArrowPressed=false;
	static bool isRightArrowPressed=false;
	static bool isZkeyPressed=false;
	static bool isXkeyPressed=false;

	while(event.pollEvent()!=0)
	{
		switch(event.type())
		{
			case SDL_QUIT:
				ShutDown();
			break;

			case SDL_KEYDOWN:
					if(event.keySym()==SDLK_UP)//<- STARTS HERE
					{
						if(currentState==GAME_STATES::MENU)
						{
								menu.previousButton();
						}
						else if(currentState==GAME_STATES::FIGHT)
						{
							isUpArrowPressed=true;
						}
					}//<-ENDS HERE
					else if(event.keySym()==SDLK_LEFT && !isLeftArrowPressed)//<- STARTS HERE
					{
						isLeftArrowPressed=true;
						 if(currentState==GAME_STATES::FIGHT)
						{
							
							mac->dodgeLeft();
						}
					}//<-ENDS HERE
					else if(event.keySym()==SDLK_RIGHT && !isRightArrowPressed) //<- STARTS HERE
					{
						isRightArrowPressed=true;
						if(currentState==GAME_STATES::FIGHT)
						{
						
							mac->dodgeRight();
						}
					} //<-ENDS HERE
					else if(event.keySym()==SDLK_z && !isZkeyPressed) //<-STARTS HERE
					{
						isZkeyPressed=true;
						if(currentState==GAME_STATES::FIGHT)
						{
						
							if(isUpArrowPressed)
							mac->headShotLeft();
							else
							mac->bodyShotLeft();
						}

					
					} //<-ENDS HERE

					else if(event.keySym()==SDLK_x && !isXkeyPressed) //<-STARTS HERE
					{
						isXkeyPressed=true;
						if(currentState==GAME_STATES::FIGHT)
						{
							

							if(isUpArrowPressed)
								mac->headShotRight();
							else
								mac->bodyShotRight();
						}
					} //<-ENDS HERE
					else if(event.keySym()==SDLK_RETURN) //<- STARTS HERE
					{	if(currentState==GAME_STATES::MENU)
						{
							menu.clickSelectedButton();
						}
						else if(currentState==GAME_STATES::FIGHT)
						{
							   fightMngr.Enter_pressed();
						}
					} //<- ENDS HERE
					else if(event.keySym()==SDLK_DOWN) //<-STARTS HERE
					{
						if(currentState==GAME_STATES::MENU)
						{
							menu.nextButton();
						}
						else if(currentState==GAME_STATES::FIGHT)
						{
						mac->block();
						}
					} //<-ENDS HERE
					
			break; //<- SDL_KEYDOWN ENDS HERE

			case SDL_KEYUP:
			if(event.keySym()==SDLK_UP)//<-STARTS HERE
			{
			isUpArrowPressed=false;
			} //<- ENDS HERE
			else if(event.keySym()==SDLK_DOWN)//<-STARTS HERE
			{
				if(currentState==GAME_STATES::FIGHT)
				{
				mac->unblock();
				}
			}//<- ENDS HERE
			else if(event.keySym()==SDLK_LEFT)//<-STARTS HERE
			{
				isLeftArrowPressed=false;
			}//<- ENDS HERE
			else if(event.keySym()==SDLK_RIGHT)//<-STARTS HERE
			{
			isRightArrowPressed=false;
			}//<- ENDS HERE
			else if(event.keySym()==SDLK_z)//<-STARTS HERE
			{
			isZkeyPressed=false;
			}//<- ENDS HERE
			else if(event.keySym()==SDLK_x)//<-STARTS HERE
			{
			isXkeyPressed=false;
			}//<- ENDS HERE
			break; ////<- SDL_KEYUP ENDS HERE

		}

	}
	

}

