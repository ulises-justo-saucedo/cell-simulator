#include <stdio.h>
#include "life_simulator.h"
int main(void) {
	/* -------------------------------------------------------------------- */
	//just some variable definitions
	//you can tweak these parameters:
	//cell_size: the size of each cell; you can put a big number to see more bigger cells in the simulation
	//seconds_between_each_generation: how many seconds the simulation will wait before passing to the next generation of cells
	//if you want to tweak how many cells are simulated (the width and height of the grid) you can go to life_simulator.h and modify GRID_WIDTH and GRID_HEIGHT directly
	const int cell_size = 5;
	int seconds_between_each_generation = 0;
	int grid[GRID_WIDTH][GRID_HEIGHT];
	int next_grid[GRID_WIDTH][GRID_HEIGHT];
	int paused = 1; //1: paused, 0: not paused
	char *simulation_state = "";
	double last_time_refresh = 0;
	/* -------------------------------------------------------------------- */
	srand(time(0));
	initialize_cells(grid);
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);
	SetTargetFPS(FPS);
	while(!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLACK);
		draw_cells(grid, cell_size);
		if(paused == 0) {
			calculate_next_cell_generation(grid, next_grid, seconds_between_each_generation, &last_time_refresh);
		}
		if(IsKeyPressed(KEY_SPACE)) {
			pause_simulation(&paused);
		}
		if(IsKeyPressed(KEY_R)) {
			randomice_simulation(grid, next_grid);
		}
		if(IsKeyPressed(KEY_C)) {
			clear_simulation(grid, next_grid);
		}
		if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
			kill_or_revive_cell(grid, next_grid, cell_size);
		}
		draw_simulation_state(simulation_state, paused);
		EndDrawing();
	}
	return 0;
}