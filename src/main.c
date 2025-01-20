#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"
#define FPS           60
#define SCREEN_WIDTH  1280
#define SCREEN_HEIGHT 640
#define TITLE         "Life Simulator"

//some parameters worth tweaking based on how the simulation will work
const int grid_width = 300;
const int grid_height = grid_width;
const int cell_size = 5;
int paused = 1; //1: paused, 0: not paused
char *simulation_state = "";
double last_time_refresh = 0;
//todo: break the code in different functions bc rn it looks horrible
void initialize_cells(int grid[grid_width][grid_height]);
void draw_cells(int grid[grid_width][grid_height], int cell_size);
void calculate_next_cell_generation(int grid[grid_width][grid_height], int next_grid[grid_width][grid_height], int seconds_between_each_generation);
void pause_simulation();
void randomice_simulation(int grid[grid_width][grid_height], int next_grid[grid_width][grid_height]);
void clear_simulation(int grid[grid_width][grid_height], int next_grid[grid_width][grid_height]);
void kill_or_revive_cell(int grid[grid_width][grid_height], int next_grid[grid_width][grid_height]);
void draw_simulation_state();
int main(void) {
	srand(time(0));
	int grid[grid_width][grid_height];
	int next_grid[grid_width][grid_height];
	initialize_cells(grid);
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);
	SetTargetFPS(FPS);
	while(!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLACK);
		draw_cells(grid, cell_size);
		if(paused == 0) {
			calculate_next_cell_generation(grid, next_grid, 0);
		}
		if(IsKeyPressed(KEY_SPACE)) {
			pause_simulation();
		}
		if(IsKeyPressed(KEY_R)) {
			randomice_simulation(grid, next_grid);
		}
		if(IsKeyPressed(KEY_C)) {
			clear_simulation(grid, next_grid);
		}
		if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
			kill_or_revive_cell(grid, next_grid);
		}
		draw_simulation_state();
		EndDrawing();
	}
	return 0;
}
void initialize_cells(int grid[grid_width][grid_height]) {
	for(int y = 0 ; y < grid_height ; y++) {
		for(int x = 0 ; x < grid_width ; x++) {
			//grid[x][y] = rand() % 2;i'll just initialize them all dead at the start
			grid[x][y] = 0;
		}
	}
}
void draw_cells(int grid[grid_width][grid_height], int cell_size) {
	//drawing the cells
	for(int y = 0 ; y < grid_height ; y++) {
		for(int x = 0 ; x < grid_width ; x++) {
			int startX = x * cell_size;
			int startY = y * cell_size;
			Color color = (grid[x][y] == 0) ? BLACK : RAYWHITE;
			DrawRectangle(startX, startY, cell_size, cell_size, color);
		}
	}
}
void calculate_next_cell_generation(int grid[grid_width][grid_height], int next_grid[grid_width][grid_height], int seconds_between_each_generation) {
	//refreshing cells
	if(GetTime() >= last_time_refresh) {
		int current_cell;
		int top_left_cell, top_cell, top_right_cell;
		int left_cell;
		int right_cell;
		int bottom_left_cell, bottom_cell, bottom_right_cell;
		int alive_cells = 0;

		for(int y = 0 ; y < grid_height ; y++) {
			for(int x = 0 ; x < grid_width ; x++) {
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
				if(x + 1 < grid_width && y - 1 >= 0) {
					top_right_cell = grid[x + 1][y - 1];
					alive_cells += (top_right_cell == 1) ? 1 : 0;
				}
				//left cell
				if(x - 1 >= 0) {
					left_cell = grid[x-1][y];
					alive_cells += (left_cell == 1) ? 1 : 0;
				}
				//right cell
				if(x + 1 < grid_width) {
					right_cell = grid[x + 1][y];
					alive_cells += (right_cell == 1) ? 1 : 0;
				}
				//bottom left cell
				if(x - 1 >= 0 && y + 1 < grid_height) {
					bottom_left_cell = grid[x - 1][y + 1];
					alive_cells += (bottom_left_cell == 1) ? 1 : 0;
				}
				//bottom cell
				if(y + 1 < grid_height) {
					bottom_cell = grid[x][y + 1];
					alive_cells += (bottom_cell == 1) ? 1 : 0;
				}
				//bottom right cell
				if(x + 1 < grid_width && y + 1 < grid_height) {
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

		for(int y = 0 ; y < grid_height ; y++) {
			for(int x = 0 ; x < grid_width ; x++) {
				grid[x][y] = next_grid[x][y];
			}
		}

		last_time_refresh = GetTime();
	}
}
void pause_simulation() {
	paused = (paused == 0) ? 1 : 0;
}
void draw_simulation_state() {
	simulation_state = (paused == 1) ? "Paused" : "";
	DrawText(simulation_state, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 30, RED);
}
void randomice_simulation(int grid[grid_width][grid_height], int next_grid[grid_width][grid_height]) {
	for(int y = 0 ; y < grid_height ; y++) {
		for(int x = 0 ; x < grid_width ; x++) {
			grid[x][y] = rand() % 2;
			next_grid[x][y] = rand() % 2;
		}
	}
}
void clear_simulation(int grid[grid_width][grid_height], int next_grid[grid_width][grid_height]) {
	for(int y = 0 ; y < grid_height ; y++) {
		for(int x = 0 ; x < grid_width ; x++) {
			grid[x][y] = 0;
			next_grid[x][y] = 0;
		}
	}
}
void kill_or_revive_cell(int grid[grid_width][grid_height], int next_grid[grid_width][grid_height]) {
	int mouseX = GetMouseX() / cell_size;
	int mouseY = GetMouseY() / cell_size;
	grid[mouseX][mouseY] = (grid[mouseX][mouseY] == 0) ? 1 : 0;
	next_grid[mouseX][mouseY] = (grid[mouseX][mouseY] == 0) ? 1 : 0;
}