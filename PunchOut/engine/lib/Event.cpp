#include "../include/Event.h"
#include <SDL2/SDL_events.h>




Event::Event()
{
 e=new SDL_Event();
}
Event::~Event()
{
	if(!e)
		delete e;
}
uint32_t Event::type()
{
	return e->type;
}

SDL_Keycode Event::keySym()
{
 	return e->key.keysym.sym;
}
uint16_t Event::keyMod()
{
	return e->key.keysym.mod;
}

int Event::pollEvent()
{
	return SDL_PollEvent(e);
}

uint8_t Event::mouseButton()
{
	return e->button.button;
}

int32_t Event::windowData1()
{
	return e->window.data1;
}

int32_t Event::windowData2()
{
	return e->window.data2;
}

uint32_t Event::windowID()
{
	return e->window.windowID;
}

uint32_t Event::windowTimeStamp()
{
	return e->window.timestamp;
}
uint32_t Event::windowEvent()
{
	return e->window.event;
}