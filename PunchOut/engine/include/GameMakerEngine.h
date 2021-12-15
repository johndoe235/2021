#ifndef __JOE_ENGINE__
#define __JOE_ENGINE__

/* C system includes */

/* C++ system includes */
#include <cstdint>
#include <string>
/* Third-party includes */

/* Own includes */

/* Forward Declaration */
struct WindowCnfg;
struct RendererCnfg;
class Renderer;
class Window;

///
class GameMakerEngine
{
public:
	GameMakerEngine();
	virtual ~GameMakerEngine();

	
	void start(WindowCnfg cnfg);

	void exit();
	void setFPS(uint32_t fps);
protected:
	void virtual onUserCreate()=0;
	void virtual handleInput()=0;
	void virtual onUserUpdate()=0;
	void virtual onUserQuit()=0;



	int32_t getWindowHeight();
	int32_t getWindowWidth();
	void ShutDown();
	
void free();
void  mainloop();

};


#endif