#include "gameEngine.hpp"

bool gameEngine::init()
{
	

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		std::cout << "Cannot initialize SDL " << std::endl;
		return false;
	}

	if (Mix_Init(MIX_INIT_MP3) == 0)
	{
		std::cout << "Cannot initialize SDL_Mixer " << SDL_GetError() <<std::endl;
		return false;
	}

	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		std::cout << "Cannot initialize SDL Image! "<< SDL_GetError() << std::endl;
		return false;
	}
	if (screenWidth == -1 || screenHeight == -1)
	{
		SDL_Rect DM;
		std::cout << SDL_GetDisplayBounds(0, &DM);
		screenWidth = DM.w;
		screenHeight = DM.h;
	}

	window = SDL_CreateWindow(this->title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->screenWidth, this->screenHeight, SDL_WINDOW_FULLSCREEN_DESKTOP);
	if (window == NULL)
	{
		std::cout << "Cannot create SDL window! " << SDL_GetError()<<std::endl;
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		std::cout << "Cannot create SDL renderer! " << SDL_GetError() << std::endl;
		return false;
	}

	if (!textureManager.init())
		return false;
	
	if (!audioManager.init())
		return false;
		
	

	return true;
}

bool gameEngine::loadData()
{
	std::string img_assets[] = { "img\\background.png","img\\play_button.png","img\\title.png","img\\protag.png","img\\sansa.png","img\\wings_final.png","img\\background0.png",
	"img\\background1.png","img\\background2.png","img\\background3.png","img\\background4.png","img\\background5.png","img\\background6.png"
		,"img\\background7.png","img\\score_texture.png",
	"img\\p1.png","img\\p2.png", "img\\p3.png", "img\\p4.png", "img\\p5.png", "img\\p6.png", "img\\p7.png", "img\\p8.png", "img\\p9.png",
	"img\\p10.png", "img\\p11.png","img\\p12.png","img\\p13.png","img\\p14.png","img\\p15.png","img\\p16.png","img\\p17.png","img\\p17.png","img\\ex_mark.png" };


	std::string img_names[] = { "background","play_button","title","protagonist","sansa","sansa_wings","background0","background1"
	,"background2" ,"background3" ,"background4","background5","background6","background7","score_texture",
		"p1", 	"p2", 	"p3", 	"p4", 	"p5", 	"p6", 	"p7", 	"p8", 	"p9", 	"p10", 	"p11", 	"p12", 	"p13", 	"p14","p15","p16","p17","p18","ex_mark" };
	if (!textureManager.loadAssets(img_assets, img_names, sizeof(img_assets) / sizeof(std::string), renderer))
		return false;


	
	std::string audio_assets[] = { "sound\\jump_sound.mp3","sound\\death_sound.mp3", "sound\\point_sound.mp3","sound\\thunder_sound.mp3" };

	std::string audio_names[] = { "jump_sound","death_sound","point_sound","thunder_sound" };

	if (!audioManager.loadChunks(audio_assets, audio_names, sizeof(audio_names)/sizeof(audio_names[0]) )) 
	{

		return false;
	}



	//create cursors
	
		cursors.push_back(SDL_CreateColorCursor(IMG_Load("cursors\\cursor1.png"),0,2));
		cursors.push_back(SDL_CreateColorCursor(IMG_Load("cursors\\cursor2.png"), 7, 1));
		if (cursors[0]==NULL || cursors[1]==NULL)
		{
			std::cout << "Cannot create SDL_cursor!" << std::endl;
			return false;
		}
		


	return true;
}

void gameEngine::gameloop()
{
	//objects go here
	
	while (!windowShouldClose)
	{
		
		
		
		//this->clear();
		//inputHandling();
		switch (game_state)
		{
		case 0:
			menu();
			break;
		case 1:
			Game();
			break;
		
		}
	
		//this->render();
	}
	

}


void gameEngine::inputHandling()
{
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			windowShouldClose = true;
		else if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_ESCAPE)
				windowShouldClose = true;

			
			
		}
		
		
		

		
	}
}



gameEngine::gameEngine(std::string title, int Width, int Height)
	:title(title), screenWidth(Width), screenHeight(Height)
{ 
	this->windowShouldClose = false;
	this->elapsedTime = 0;

	
}

SDL_Event* gameEngine::getEventHandler()
{
	return &e;
}

void gameEngine::run()
{
	if (init())
	{
		
		if (loadData())
		{
			
			gameloop();
		}
		
	}
	
	exit();

}

void gameEngine::render()
{
	SDL_RenderPresent(renderer);
}

void gameEngine::clear()
{
	SDL_RenderClear(renderer);
}

bool gameEngine::rectCollision(SDL_Rect* A, SDL_Rect* B)
{
	
	if (A->x + A->w < B->x || B->x + B->w < A->x)
		return false;
	if (A->y + A->h - 2 < B->y || B->y + B->h < A->y)
		return false;

	return true;
}

bool gameEngine::mouseCollision(SDL_Rect* A)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	if (x<A->x || x>A->x + A->w)
		return false;
	if (y<A->y || y>A->y + A->h)
		return false;

	return true;
}

void gameEngine::shouldWindowClose(bool state)
{
	this->windowShouldClose = state;
}

void gameEngine::change_gameState(int state)
{
	this->game_state = state;
}

void gameEngine::setRenderColor(int r, int g, int b)
{
	this->r = r;
	this->g = g;
	this->b = b;
	SDL_SetRenderDrawColor(renderer, r, g, b,255);
}

int gameEngine::getScreenW()
{
	return screenWidth;
}

 int gameEngine::getScreenH()
{
	return screenHeight;
}

SDL_Renderer* gameEngine::getRenderer()
{
	return renderer;
}



Uint32 gameEngine::getElapsedTime()
{
	return elapsedTime;
}

void gameEngine::exit()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	for (SDL_Cursor* &cursor : cursors)
		SDL_FreeCursor(cursor);
	textureManager.exit();
	audioManager.exit();
	//gameLogic.exit();
	IMG_Quit();
	Mix_Quit();
	SDL_Quit();
}




