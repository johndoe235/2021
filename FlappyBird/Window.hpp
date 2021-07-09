#pragma once
#include <SDL.h>

class Window
{
	public:

		Window(const std::string title, int Width, int Heigth);

	void Present();
	void Clear();
	int getW();
	int getH();
	void changeRGB(int r,int g,int b);
	
	SDL_Renderer* getRenderer();
	void DestroyWindow();
	

	private:
		SDL_Window* window;
		SDL_Renderer* renderer;
		
		int w, h;
		int r, g, b;
	};
