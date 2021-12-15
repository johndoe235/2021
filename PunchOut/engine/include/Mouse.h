#ifndef __JOE_MOUSE__
#define __JOE_MOUSE__

/* C system includes */

/* C++ system includes */
#include <cstdint>
/* Third-party includes */

/* Own includes */

/* Forward Declaration */

///


namespace mouse
{

	uint32_t getMouseCoordinates(int32_t* x,int32_t* y);
	uint32_t getGlobalMouseCoordinates(int32_t* x,int32_t* y);

	int32_t getMouseX();
	int32_t getMouseY();



}
#endif