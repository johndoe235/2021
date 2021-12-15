#include <SDL2/SDL_video.h>
#include <SDL2/SDL_error.h>
#include "../include/Window.h"
#include <iostream>
Window::Window()
{

}
Window::~Window()
{
	free();
}
bool Window::init(WindowCnfg cnfg)
{

	if(pWindow!=nullptr)
		SDL_DestroyWindow(pWindow);

	pWindow=SDL_CreateWindow(cnfg.title.c_str(),SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,cnfg.windowWidth,cnfg.windowHeight,cnfg.displayMode);

	SCREEN_WIDTH=cnfg.windowWidth;
	SCREEN_HEIGHT=cnfg.windowHeight;

	if(pWindow!=nullptr)
	{
		running=true;
		return true;
	}
	else
		std::cerr<<"Cannot create Window! "<<SDL_GetError()<<std::endl;

return false;
}

void Window::free()
{
	if(!pWindow) //==nullptr
		SDL_DestroyWindow(pWindow);
}
bool Window::isWindowRunning()
{
	return !running;
}
void Window::WindowClose()
{
	running=false;
}

int32_t Window::getWidth()
{
return SCREEN_WIDTH;
}
int32_t Window::getHeight()
{
	return SCREEN_HEIGHT;
}
void Window::refreshSize()
{
	SDL_GetWindowSize(pWindow,&SCREEN_WIDTH,&SCREEN_HEIGHT);
}

void Window::setWindowSize(int32_t w,int32_t h)
{
	SDL_SetWindowSize(pWindow,w,h);
}
void Window::getWindowPosition(int32_t* w,int32_t* h)
{
	SDL_GetWindowPosition(pWindow,w,h);
                        
}
/*
SDL_Window* Window::getSDL_Window()
{
	return pWindow;
}
*/

