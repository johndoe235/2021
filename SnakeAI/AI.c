#include "structures.h"
#include "AI.h"

bool AI_start(AI* ai, int M, int N)
{
	{
		ai->dp = calloc(M, sizeof(node*));

		if (ai->dp == NULL)
			return false;

		for (int i = 0; i < M; i++)
		{
			ai->dp[i] = calloc(N, sizeof(node));

		}


	}
	ai->M = M;
	ai->N = N;

	printf("AI start:Success! %d %d\n", M, N);
	return true;
}
bool AI_dfs(int row, int col, int h_number, AI* ai)
{



	if (row < 0 || col < 0 || row >= ai->M || col >= ai->N)
		return false;

	if (h_number == ai->M * ai->N + 1 && row == 0 && col == 0)
	{
		return true;
	}
	else
	{

		if (ai->dp[row][col].value != 0)
			return false;

		ai->dp[row][col].value = h_number;

		//EAST
		if (AI_dfs(row, col + 1, h_number + 1, ai))
		{
			ai->dp[row][col].movement = EAST;
			return true;
		}
		//NORTH
		if (AI_dfs(row - 1, col, h_number + 1, ai))
		{
			ai->dp[row][col].movement = NORTH;
			return true;
		}
		//SOUTH
		if (AI_dfs(row + 1, col, h_number + 1, ai))
		{
			ai->dp[row][col].movement = SOUTH;
			return true;
		}
		//WEST
		if (AI_dfs(row, col - 1, h_number + 1, ai))
		{
			ai->dp[row][col].movement = WEST;
			return true;
		}

		ai->dp[row][col].value = 0;
	}

	return false;

}
bool AI_gen_hamilton(AI* ai)
{
	if (AI_dfs(0, 0, 1, ai))
	{
		printf("AI has found a Hamilton Cycle!");
		
		return  true;
	}
	printf("AI has not found a Hamilton Cycle!");
	return false;
}

void AI_exit(AI* ai)
{
	for (int i = 0; i < ai->M; i++)
	{

		free(ai->dp[i]);
		ai->dp[i] = 0;

	}
	free(ai->dp);

}

bool get_shortcut(snake* snake, AI* ai,rabbit* rabbit)
{
	if (snake->movement == EAST || snake->movement == WEST)
	{
		int y = snake->body[0].y;
		int x= snake->body[0].x;
		
		if (y-1 > 0)
		{
			int value = ai->dp[y - 1][x].value;

			if (value > ai->dp[y][x].value && value < ai->dp[rabbit->p.y][rabbit->p.x].value)
			{
				snake->movement = NORTH;
				snake->moves_since_last_shortcut++;
				return true;
			}

		}
		else if (y + 1 < ai->M)
		{
			int value = ai->dp[y + 1][x].value;

			if (value > ai->dp[y][x].value && value < ai->dp[rabbit->p.y][rabbit->p.x].value)
			{
				snake->movement = SOUTH;
				snake->moves_since_last_shortcut++;
				return true;
			}
		}
	}
	else if (snake->movement == NORTH || snake->movement == SOUTH)
	{
		int y = snake->body[0].y;
			int x = snake->body[0].x;

		if (x - 1 > 0)
		{
			int value = ai->dp[y][x-1].value;

			if (value > ai->dp[y][x].value && value < ai->dp[rabbit->p.y][rabbit->p.x].value)
			{
				snake->movement = WEST;
				snake->moves_since_last_shortcut++;
				return true;
			}
			else if (x+1 < ai->N)
			{
				int value = ai->dp[y][x + 1].value;
				if (value > ai->dp[y][x].value&& value < ai->dp[rabbit->p.y][rabbit->p.x].value)
				{
					snake->movement = EAST;
					snake->moves_since_last_shortcut++;
					return true;
				}

			}
		}


	}
	return false;
}



void AI_make_move(snake* snake, AI* ai, rabbit* rabbit)
{
	if (snake->body[0].y < ai->M && snake->body[0].x < ai->N)
		snake->movement = ai->dp[snake->body[0].y][snake->body[0].x].movement;

	if (snake->moves_since_last_shortcut+1 > snake->size)
	{
		if (get_shortcut(snake, ai, rabbit))
			snake->moves_since_last_shortcut = 0;
		return;
	}
	snake->moves_since_last_shortcut++;
	


}

/*
void AI_make_move(snake* snake, AI* ai, rabbit* target)
{
	
	if (snake->moves_since_last_shortcut+1 > snake->size)
	{
		int north, south, west, east;
		
		north = south = west = east = 0;
		if (snake->movement != SOUTH && (snake->body[0].y-1>=0) )
		{
			north = ai->dp[snake->body[0].y-1][snake->body[0].x].value;
			
			
		}
		if (snake->movement != EAST && (snake->body[0].x - 1 >= 0))
		{
			west = ai->dp[snake->body[0].y][snake->body[0].x-1].value;
		
		}
		if (snake->movement != NORTH && (snake->body[0].y+1  < ai->M))
		{
			south = ai->dp[snake->body[0].y+1][snake->body[0].x].value;
			
		}
		if (snake->movement != WEST && (snake->body[0].x + 1 < ai->N))
		{
			east = ai->dp[snake->body[0].y][snake->body[0].x+1].value;
			
		}
		
		int target_value = ai->dp[target->p.y][target->p.x].value;
		int snake_value = ai->dp[snake->body[0].y][snake->body[0].y].value;
		
		
			int best_value = max(max(north, south), max(east,west));

			if (best_value == north)
				snake->movement = NORTH;
			else if(best_value== south)
				snake->movement = SOUTH;
			else if(best_value==west)
				snake->movement = WEST;
			else if(best_value==east)
				snake->movement = EAST;

		snake->moves_since_last_shortcut=0;
			

		
		
	}
	else
	{
		if (snake->body[0].y < ai->M && snake->body[0].x < ai->N)
			snake->movement = ai->dp[snake->body[0].y][snake->body[0].x].movement;
	}
	snake->moves_since_last_shortcut++;
}
*/
void AI_print_cycle(AI* ai)
{
	for (int i = 0; i < ai->M; i++)
	{
		for (int j = 0; j < ai->N; j++)
			printf("| %d |", ai->dp[i][j].movement);
		printf("\n");
	}



}


