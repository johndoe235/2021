#include "gameEngine.hpp"



int main(int argc, char* argv[])
{
	
	//SDL_GetCurrentDisplayMode(0, &DM);
	

	gameEngine App("Flappy T", -1, -1);
	
	App.run();
	
	return 0;
}