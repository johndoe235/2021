#ifndef __JOE_TIMER__
#define __JOE_TIMER__


/* C system includes */

/* C++ system includes */
#include <cstdint>
/* Third-party includes */

/* Own includes */

/* Forward Declaration */


/*                    */



namespace timer
{

	
	uint32_t GetTicks();
	uint64_t GetPerformanceCounter();
	void sleep(uint32_t ms);

	class FrameRateControl
	{
	public:
		FrameRateControl(uint32_t desired_fps);
		void begin();
		void end();
	private:
		uint32_t fps;
		uint32_t delta;
		uint32_t desired_delta;
		uint32_t start;
		
	};



}
#endif