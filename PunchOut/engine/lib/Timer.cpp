#include <SDL2/SDL_timer.h>
#include "../include/Timer.h"

namespace timer
{

uint32_t GetTicks()
{
	return SDL_GetTicks();
}
uint64_t GetPerformanceCounter()
{
 return SDL_GetPerformanceCounter();
}
void sleep(uint32_t ms)
{
	SDL_Delay(ms);
}

FrameRateControl::FrameRateControl(uint32_t desired_fps)
:fps(desired_fps),delta(0)
{
	desired_delta=1000/fps;
}

void FrameRateControl::begin()
{
	start=GetTicks();
}
void FrameRateControl::end()
{
	delta=GetTicks()-start;

	if(delta<desired_delta)
		sleep(desired_delta-delta);
}

}