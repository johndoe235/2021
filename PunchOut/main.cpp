#include <string>
#include "game/include/Game.h"

#include <cstdint>
#include <iostream>


int32_t main([[maybe_unused]]int argc, [[maybe_unused]]char* args[]) 
{
	
	Game app;
	
	app.start(WindowCnfg{(SHOWN),860,640,"Game"});
	app.exit();

return 0;
}