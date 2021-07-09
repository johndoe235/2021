#include "scoreboard.h"


Scoreboard::Scoreboard(SDL_Texture* texture, int ScreenW, int ScreenH)
	:texture(texture), ScreenWidth(ScreenW), ScreenHeight(ScreenH)
{
	this->source = { 0,0,75,96 };
	this->dest = { ScreenWidth / 2 - 50,5,50,60 };
	this->lastNumber = -1;
	size = 1;

}

Scoreboard::Scoreboard()
{
}

void Scoreboard::render(SDL_Renderer* renderer)
{
	std::stack<SDL_Rect> stack;
	getScoreRects(&stack);

	if (stack.size() > 1)
		dest = { ScreenWidth / 2 - (int)stack.size() * dest.w,5,50,60 };

	while (stack.size() > 0)
	{
		source = stack.top();
		stack.pop();
		SDL_RenderCopy(renderer, texture, &source, &dest);
		this->dest.x += dest.w;
	}
	dest = { ScreenWidth / 2 - 50,5,50,60 };;
}



void Scoreboard::addPoint()
{
	addToScore();



	if (size == 1 && score[2] != -1)size = 2;
	if (size == 2 && score[1] != -1)size = 3;
	if (size == 3 && score[0] != -1)size = 4;


}

void Scoreboard::addToScore()
{

	score[3] += 1;
	for (int i = 3; i > 0; i--)
	{

		if (score[i] > 9)
		{
			score[i] = 0;
			if (score[i - 1] != -1)
				score[i - 1] += 1;
			else
				score[i - 1] = 1;
		}
	}


}
bool Scoreboard::checkScore(SDL_Rect* bird, SDL_Rect* pipe, int pipeNumber)
{
	

	if (bird->x + bird->w >= pipe->x + pipe->w / 2 && bird->x + bird->w <= pipe->x + pipe->w)
	{

		if (lastNumber != pipeNumber)
		{

			lastNumber = pipeNumber;
			addPoint();
			return true;

		}


	}
	return false;
}

void Scoreboard::reset()
{
	this->source = { 0,0,75,96 };
	this->dest = { ScreenWidth / 2 - 50,5,50,60 };
	for (int i = 0; i < 4; i++)
		score[i] = -1;
	score[3] = 0;
}

void Scoreboard::onDeathUpdate(SDL_Renderer* renderer)
{
	render(renderer);
}

bool Scoreboard::update(SDL_Renderer* renderer, SDL_Rect* protag, std::vector<Painting> &paintings)
{
	bool point_up = false;
	for (auto& painting : paintings)
	{
		if (checkScore(protag, &painting.getDest(), painting.getID()))
			point_up = true;
	}
	render(renderer);
	return point_up;
}



SDL_Rect Scoreboard::getNumberRect(int number)
{
	int x, y, w, h;
	x = coordinates[number][0];
	y = coordinates[number][1];
	w = coordinates[number][2];
	h = coordinates[number][3];

	return SDL_Rect{ x,y,w,h };
}


void Scoreboard::getScoreRects(std::stack<SDL_Rect>* stack)
{

	for (int i = 3; i >= 0; i--)
		if (score[i] == -1)
			break;
		else
		{
			stack->push(getNumberRect(score[i]));
		}
}



