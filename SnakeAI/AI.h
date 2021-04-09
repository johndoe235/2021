#pragma once
#pragma once
#include "structures.h"





bool AI_start(AI* ai, int M, int N);
bool AI_gen_hamilton(AI* ai);
bool AI_dfs(int row, int col, int h_number, AI* ai);
void AI_exit(AI* ai);
void AI_make_move(snake* snake, AI* ai,rabbit* rabbit);
void AI_print_cycle(AI* ai);