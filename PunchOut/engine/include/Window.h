#ifndef __JOE_WINDOW__
#define __JOE_WINDOW__

/* C system includes */

/* C++ system includes */
#include <cstdint>
/* Third-party includes */

/* Own includes */
#include "cnfg/WindowCnfg.h"
/* Forward Declaration */
struct WindowCnfg;
struct SDL_Window;
class Renderer;


class Window
{
	public:
		Window();
		~Window();
		bool init(WindowCnfg cnfg);
		void free();

		bool isWindowRunning();
		void WindowClose();
		int32_t getWidth();
		int32_t getHeight();
		void refreshSize();
		void setWindowSize(int32_t w,int32_t h);
		void getWindowPosition(int32_t* w,int32_t* h);
		//SDL_Window* getSDL_Window();
		friend class Renderer;
	private:
	bool running=false;
	int32_t SCREEN_WIDTH=0;
	int32_t SCREEN_HEIGHT=0;
	SDL_Window* pWindow=nullptr;

};
#endif