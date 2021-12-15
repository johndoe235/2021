#include "../include/Renderer.h"
#include <SDL2/SDL_render.h>
#include <iostream>
#include "../include/Window.h"
#include "../include/Texture.h"
bool Renderer::init(Window& Window,RendererFlags flag)
{
	if(pRenderer!=nullptr)
			SDL_DestroyRenderer(pRenderer);

		pRenderer=SDL_CreateRenderer(Window.pWindow,-1,static_cast<uint32_t>(flag));

		if(pRenderer!=nullptr)
			return true;
		
		else
		{
			std::cerr<<"Cannot create Renderer! "<<SDL_GetError()<<"\n";
			return false;

		}
	
}

void Renderer::free()
{
	if(!pRenderer)
		SDL_DestroyRenderer(pRenderer);
}

void Renderer::changeRGB(uint8_t r,uint8_t g,uint8_t b,uint8_t a)
{
	SDL_SetRenderDrawColor(pRenderer,r,g,b,a);
}
void Renderer::clear()
{
	SDL_RenderClear(pRenderer);
}
void Renderer::present()
{
	SDL_RenderPresent(pRenderer);
} 

void Renderer::FillRectangle(SDL_Rect*& rect)
{
	SDL_RenderFillRect(pRenderer,rect);
}

void Renderer::drawRaw(SDL_Texture* texture, SDL_Rect* source,  SDL_Rect* dest)
{
	SDL_RenderCopy(pRenderer,texture,source,dest);
}
void Renderer::drawEx(Texture* texture,const SDL_Rect* srcrect,const SDL_Rect* dstrect,  const double angle,  const SDL_Point* center,const RendererFlip& flip)
{
	SDL_RenderCopyEx(pRenderer,texture->pTexture,srcrect,dstrect,angle,center,static_cast<SDL_RendererFlip>(flip));
}

void Renderer::blendMode(RendererBlendMode mod)
{
	SDL_SetRenderDrawBlendMode(pRenderer,static_cast<SDL_BlendMode>(mod));
}
void Renderer::drawLine(int x1,int y1,int x2,int y2)
{
		SDL_RenderDrawLine(pRenderer,x1,y1,x2,y2);
}
void Renderer::drawLines(SDL_Point*& points,int count)
{
		SDL_RenderDrawLines(pRenderer,points,count);
}
void Renderer::drawPoint(int x,int y)
{
SDL_RenderDrawPoint(pRenderer,x, y);
}
void Renderer::drawPoints(SDL_Point*& points,int count)
{
		SDL_RenderDrawPoints(pRenderer,points,count);
}

/*	
SDL_Renderer* Renderer::getSDLRenderer()
{
	return pRenderer;
}
*/