#ifndef __JOE__EVENT__
#define __JOE__EVENT__


/* C system includes */

/* C++ system includes */
#include <cstdint>
/* Third-party includes */
#include <SDL_keycode.h>
/* Own includes */

/* Forward Declaration */





union SDL_Event;
class Event
{
public:
	Event();
	~Event();

	uint32_t type();
	SDL_Keycode keySym();
	uint16_t keyMod();
	int pollEvent();
	uint8_t mouseButton();
	int32_t windowData1();
	int32_t windowData2();
	uint32_t windowID();
	uint32_t windowTimeStamp();
	uint32_t windowEvent();

private:
	SDL_Event* e;

};

#endif