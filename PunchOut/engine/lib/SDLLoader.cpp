#include "../include/SDLLoader.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

/*
SDLLoader::SDLLoader()()
{



}
SDLLoader::~SDLLoader()
{
	free();
}
*/

namespace SDLLoader{

bool init(SDLInitFlags SDLflag,IMGInitFlags IMGflag,MIXInitFlags MIXflag)
{
	if(SDL_Init(SDLflag)!=0){
		std::cerr<<"Cannot initialize  SDL! "<<SDL_GetError()<<"\n";
		return false;
	}
	if(IMG_Init(IMGflag)==0)
	{
		std::cerr<<"Cannot initialize  IMG! "<<IMG_GetError()<<"\n";
		return false;
	}
		if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024)==-1) 
		{
    	std::cerr<<"Mix_OpenAudio: "<< Mix_GetError()<<"\n";
    	return false;
		}
	if(Mix_Init(MIXflag)!=MIXflag)
	{
		std::cerr<<"Cannot initialize  Mixer! "<<Mix_GetError()<<"\n";
		return false;

		

   		
	}

	if(TTF_Init()==-1)
	{
		std::cerr<<"Cannot initialize  TTF! "<<TTF_GetError()<<"\n";
		return false;
	}


	return true;
}

void free()
{
	TTF_Quit();

	Mix_CloseAudio();

	Mix_Quit();
	IMG_Quit();
	SDL_Quit();

}

}