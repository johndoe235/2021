#include <SDL.h>
#include <iostream>
#include "Window.hpp"


Window::Window(const std::string title, int Width, int Heigth)
	:window(NULL), renderer(NULL), w(Width), h(Heigth), r(0), g(0), b()
{
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,Width,Heigth ,SDL_WINDOW_SHOWN);

	if (window == NULL)
		std::cout << "Cannot create Window!" << SDL_GetError() << std::endl;

	renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED || SDL_RENDERER_PRESENTVSYNC);
	
	if (renderer == NULL)
		std::cout << "Cannot create Renderer!" << SDL_GetError() << std::endl;




}

void Window::Clear()
{
	
		SDL_SetRenderDrawColor(renderer, r, g, b, 255);
		SDL_RenderClear(renderer);
	

}
void Window::Present()
{
	SDL_RenderPresent(renderer);
}
SDL_Renderer* Window::getRenderer()
{
	return renderer;
}
void Window::DestroyWindow()
{
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
}

int Window::getW()
{
	return this->w;
}
int Window::getH()
{
	return this->h;
}
void Window::changeRGB(int r, int g, int b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}

