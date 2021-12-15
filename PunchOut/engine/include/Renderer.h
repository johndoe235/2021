#ifndef __JOE_RENDERER__
#define __JOE_RENDERER__

/* C system includes */

/* C++ system includes */
#include <cstdint>
/* Third-party includes */

/* Own includes */
#include "utils/RendererEnums.h"
/* Forward Declaration */
struct SDL_Rect;
struct SDL_Point;
struct SDL_Texture;
struct SDL_Window;
struct SDL_Renderer;
class Texture;
class Window;
/*                    */


class Renderer
{
public:
  Renderer() = default;

  Renderer(const Renderer& other) = delete;
  Renderer& operator=(const Renderer& other) = delete;

  Renderer(Renderer&& other) = delete;
  Renderer& operator=(Renderer&& other) = delete;


	bool init(Window& window,RendererFlags flag=RendererFlags::ACCELERATED);
	void free();

	void changeRGB(uint8_t r,uint8_t g,uint8_t b,uint8_t a=255);

	void clear();
	void present(); //swap buffers

	void FillRectangle(SDL_Rect*& rect);

	
	void drawRaw(SDL_Texture* pTexture, SDL_Rect* source,  SDL_Rect* dest);
	void drawEx(Texture* texture,const SDL_Rect* srcrect,const SDL_Rect* dstrect,  const double angle,  const SDL_Point* center,const RendererFlip& flip);
	void drawTextureOnly(SDL_Texture* pTexture);
	void blendMode(RendererBlendMode mod);
	

	void drawLine(int x1,int y1,int x2,int y2);
	void drawLines(SDL_Point*& points,int count);
	void drawPoint(int x,int y);
	void drawPoints(SDL_Point*& points,int count);

	//SDL_Renderer* getSDLRenderer();
	friend class Texture;
private:
	SDL_Renderer* pRenderer;
};

#endif