#include "../include/GameMakerEngine.h"
#include "../include/SDLLoader.h"

#include "../include/cnfg/WindowCnfg.h"
#include "../include/Timer.h"

#include "../include/Window.h"
#include "../include/Renderer.h"
#include <iostream>

#include "../include/managers/DrawManager.h"
#include "../include/managers/ResourceManager.h"
GameMakerEngine::GameMakerEngine()
{
	
}
GameMakerEngine::~GameMakerEngine()
{
	if(DrawMngr!=nullptr)
	free();

	

}


void GameMakerEngine::start(WindowCnfg cnfg)
{

	DrawMngr=DrawManager::getInstance();
	ResourceMngr=ResourceManager::getInstance();
	if(!SDLLoader::init())
		return;


	if(DrawMngr->init(cnfg))
	{
	mainloop();
	}

}

void GameMakerEngine::exit()
{
	free();
}


void GameMakerEngine::free()
{
	ResourceMngr->free();
	DrawMngr->free();

	SDLLoader::free();
	
	DrawMngr=nullptr;
	ResourceMngr=nullptr;
	//std::cout<<"Freed\n";
}

void GameMakerEngine::mainloop()
{
	timer::FrameRateControl fpsControl(60);
	onUserCreate();
	while(!DrawMngr->window->isWindowRunning())
	{
		fpsControl.begin();

		DrawMngr->renderer->clear();

		handleInput();
		onUserUpdate();
		
		DrawMngr->renderer->present();

		fpsControl.end();
	}
	onUserQuit();
}

int32_t GameMakerEngine::getWindowHeight()
{
	return DrawMngr->window->getHeight();
}
int32_t GameMakerEngine::getWindowWidth()
{
	return DrawMngr->window->getWidth();
}

void GameMakerEngine::ShutDown()
{
	DrawMngr->window->WindowClose();
}
