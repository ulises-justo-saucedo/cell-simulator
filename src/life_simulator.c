#include "life_simulator.h"
void initialize_cells(int grid[GRID_WIDTH][GRID_HEIGHT]) {
	for(int y = 0 ; y < GRID_HEIGHT ; y++) {
		for(int x = 0 ; x < GRID_WIDTH ; x++) {
			grid[x][y] = 0;
		}
	}
}
void draw_cells(int grid[GRID_WIDTH][GRID_HEIGHT], int cell_size) {
	for(int y = 0 ; y < GRID_HEIGHT ; y++) {
		for(int x = 0 ; x < GRID_WIDTH ; x++) {
			int startX = x * cell_size;
			int startY = y * cell_size;
			Color color = (grid[x][y] == 0) ? BLACK : RAYWHITE;
			DrawRectangle(startX, startY, cell_size, cell_size, color);
		}
	}
}
void calculate_next_cell_generation(int grid[GRID_WIDTH][GRID_HEIGHT], int next_grid[GRID_WIDTH][GRID_HEIGHT], int seconds_between_each_generation, double *last_time_refresh) {
	//refreshing cells
	if(GetTime() >= *last_time_refresh) {
		int current_cell;
		int top_left_cell, top_cell, top_right_cell;
		int left_cell;
		int right_cell;
		int bottom_left_cell, bottom_cell, bottom_right_cell;
		int alive_cells = 0;

		for(int y = 0 ; y < GRID_HEIGHT ; y++) {
			for(int x = 0 ; x < GRID_WIDTH ; x++) {
				alive_cells = 0;
				current_cell = grid[x][y];
				//top_left_cell
				if(x - 1 >= 0 && y - 1 >= 0) {
					top_left_cell = grid[x - 1][y - 1];
					alive_cells += (top_left_cell == 1) ? 1 : 0;
				}
				//top_cell
				if(y - 1 >= 0) {
					top_cell = grid[x][y - 1];
					alive_cells += (top_cell == 1) ? 1 : 0;
				}
				//top_right_cell
				if(x + 1 < GRID_WIDTH && y - 1 >= 0) {
					top_right_cell = grid[x + 1][y - 1];
					alive_cells += (top_right_cell == 1) ? 1 : 0;
				}
				//left cell
				if(x - 1 >= 0) {
					left_cell = grid[x-1][y];
					alive_cells += (left_cell == 1) ? 1 : 0;
				}
				//right cell
				if(x + 1 < GRID_WIDTH) {
					right_cell = grid[x + 1][y];
					alive_cells += (right_cell == 1) ? 1 : 0;
				}
				//bottom left cell
				if(x - 1 >= 0 && y + 1 < GRID_HEIGHT) {
					bottom_left_cell = grid[x - 1][y + 1];
					alive_cells += (bottom_left_cell == 1) ? 1 : 0;
				}
				//bottom cell
				if(y + 1 < GRID_HEIGHT) {
					bottom_cell = grid[x][y + 1];
					alive_cells += (bottom_cell == 1) ? 1 : 0;
				}
				//bottom right cell
				if(x + 1 < GRID_WIDTH && y + 1 < GRID_HEIGHT) {
					bottom_right_cell = grid[x + 1][y + 1];
					alive_cells += (bottom_right_cell == 1) ? 1 : 0;
				}
				if(current_cell == 1) {
					if(alive_cells < 2) {
						next_grid[x][y] = 0;
					} else if (alive_cells == 3) {
						next_grid[x][y] = current_cell;
					} else if (alive_cells > 3) {
						next_grid[x][y] = 0;
					}
				} else if(current_cell == 0) {
					if(alive_cells == 3) {
						next_grid[x][y] = 1;
					}
				}
			}
		}

		for(int y = 0 ; y < GRID_HEIGHT ; y++) {
			for(int x = 0 ; x < GRID_WIDTH ; x++) {
				grid[x][y] = next_grid[x][y];
			}
		}

		*last_time_refresh = GetTime();
	}
}
void pause_simulation(int *paused) {
	*paused = (*paused == 0) ? 1 : 0;
}
void draw_simulation_state(char *simulation_state, int paused) {
	simulation_state = (paused == 1) ? "Paused" : "";
	DrawText(simulation_state, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 30, RED);
}
void randomice_simulation(int grid[GRID_WIDTH][GRID_HEIGHT], int next_grid[GRID_WIDTH][GRID_HEIGHT]) {
	for(int y = 0 ; y < GRID_HEIGHT ; y++) {
		for(int x = 0 ; x < GRID_WIDTH ; x++) {
			grid[x][y] = rand() % 2;
			next_grid[x][y] = rand() % 2;
		}
	}
}
void clear_simulation(int grid[GRID_WIDTH][GRID_HEIGHT], int next_grid[GRID_WIDTH][GRID_HEIGHT]) {
	for(int y = 0 ; y < GRID_HEIGHT ; y++) {
		for(int x = 0 ; x < GRID_WIDTH ; x++) {
			grid[x][y] = 0;
			next_grid[x][y] = 0;
		}
	}
}
void kill_or_revive_cell(int grid[GRID_WIDTH][GRID_HEIGHT], int next_grid[GRID_WIDTH][GRID_HEIGHT], int cell_size) {
	int mouseX = GetMouseX() / cell_size;
	int mouseY = GetMouseY() / cell_size;
	grid[mouseX][mouseY] = (grid[mouseX][mouseY] == 0) ? 1 : 0;
	next_grid[mouseX][mouseY] = (grid[mouseX][mouseY] == 0) ? 1 : 0;
}