#pragma once
#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>


enum Movement
{
	NORTH,
	WEST,
	SOUTH,
	EAST
};

typedef struct position
{
	int x;
	int y;
}position;

typedef struct snake
{
	bool alive;
	uint32_t size;
	uint32_t max_size;
	int movement;
	position* body;
	uint32_t moves_since_last_shortcut;
	

}snake;

typedef struct rabbit
{
	position p;
	bool alive;
}rabbit;



typedef struct node
{
	int value;
	int movement;
}node;

typedef struct AI
{
	node** dp;
	int M;
	int N;
	bool active;
	bool hamilton_cycle;
}AI;



