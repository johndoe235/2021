#ifndef __JOE_TEXTURE__
#define __JOE_TEXTURE__



/* C system includes */

/* C++ system includes */
#include <string>
#include <cstdint>
/* Third-party includes */

/* Own includes */
#include "../include/Renderer.h"
/* Forward Declaration */
struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Surface;

/*                    */





class Texture
{
public:
	Texture();
  ~Texture();
	Texture(Renderer*& renderer,std::string path);

  Texture(const Texture& other) = delete;
  Renderer& operator=(const Texture& other) = delete;

  Texture(Texture&& other) = delete;
  Texture& operator=(Texture&& other) = delete;
  //SDL_Texture*& getRawTexture();

  void free();

  bool createTexture(Renderer*& renderer,std::string path);
  bool createTextureFromSurface(Renderer*& renderer,SDL_Surface*& surface);
  void setAlphaMod(uint8_t alpha);
  void setBlendMode(RendererBlendMode mode);
  void setTextureColorMode(uint8_t r,uint8_t g,uint8_t b);

  friend class Renderer;
protected:
	SDL_Texture* pTexture;
};




#endif