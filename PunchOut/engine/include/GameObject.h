#ifndef __JOE_GAME_OBJECT__
#define __JOE_GAME_OBJECT__

/* C system includes */

/* C++ system includes */
#include <cstdint>
#include <string>
/* Third-party includes */

/* Own includes */
#include "utils/RendererEnums.h"
/* Forward Declaration */
class Renderer;
class Texture;
struct  SDL_Rect;
struct SDL_Point;
class GameObject
///



{
public:
	 virtual ~GameObject();
		void moveUp(int32_t x);
		void moveDown(int32_t x);
		void moveLeft(int32_t x);
		void moveRight(int32_t x);
		void rotate(double degrees);
		void setPosition(int x,int y,int w,int h);
		void setPosition(SDL_Rect*& destination);
		void setSourcePosition(int x,int y,int w,int h);
		void setSourcePositionRaw( SDL_Rect* source);
		void virtual draw();
		//Texture* getTexture();

		//bool loadTexture(std::string path,Renderer*& renderer);
		void setTextureFlip_NONE();
		void setTextureFlip_HORIZONTAL();
		void setTextureFlip_VERTICAL();

		bool isTextureFlipped();
		bool isTextureFlipped_HORIZONTAL();
		bool isTextureFlipped_VERTICAL();

		int getWidth();
		int getHeight();
		int getXposition();
		int getYposition();

		void setWidth(int amount);
		void setHeight(int amount);
		void setXposition(int amount);
		void setYposition(int amount);

		static bool loadTexture(uint32_t index,std::string path);
		static Texture* getTexture(uint32_t texture_index);
		static int32_t getScreenWidth();
		static int32_t getScreenHeight();
		static bool loadMusic(uint32_t index,std::string path);
		static bool loadSound(uint32_t index,std::string path);
		static bool playMusic(uint32_t index,int loops=0);
    	static bool playSound(uint32_t index,int loops=0);
		static void pauseMusic();
		static void resumeMusic();

		void setTexture(uint32_t texture_name);
		void setTexture(Texture* texture);
		void Fill(uint8_t r,uint8_t g,uint8_t b);
		void changeTextureColorMod(uint8_t r,uint8_t g,uint8_t b);
protected:
	void allocate_center();
	void allocate_source();
	void allocate_dest();
	void allocate_texture();

	void deallocate_center();
	void deallocate_source();
	void deallocate_dest();
	void deallocate_texture();
	void unoverridable_draw();

	SDL_Point* center=0;//// User must allocate and delete memory.
	SDL_Rect* source=0;//// User must allocate and delete memory.
	SDL_Rect* dest=0;//// User must allocate and delete memory.
	Texture* texture=0;//// User must allocate and delete memory.
	
	RendererFlip flip=RendererFlip::FLIP_NONE;
	double angle=0;

	
	private:
bool _hasSourceAllocated=false;
bool _hasDestAllocated=false;
bool _hasTextureAllocated=false;
bool _hasCenterAllocated=false;



};
#endif