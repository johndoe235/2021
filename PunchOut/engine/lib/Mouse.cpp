#include "../include/Mouse.h"
#include <SDL2/SDL_mouse.h>


namespace mouse
{
uint32_t getMouseCoordinates(int32_t* x,int32_t* y)
{
	return SDL_GetMouseState(x,y);
}
uint32_t getGlobalMouseCoordinates(int32_t* x,int32_t* y)
{
	return SDL_GetGlobalMouseState(x,y);
}

int32_t getMouseX()
{
	int32_t x;
	SDL_GetMouseState(&x,NULL);
	return x;
}
int32_t getMouseY()
{
	int32_t y;
	SDL_GetMouseState(NULL,&y);
	return y;
}
}