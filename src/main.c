#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"
#define FPS           60
#define SCREEN_WIDTH  1280
#define SCREEN_HEIGHT 640
#define TITLE         "Life Simulator"
//todo: break the code in different functions bc rn it looks horrible
int main(void) {
	srand(time(0));
	int paused = 1;
	double last_time_refresh = 0;
	int width = 300;
	int height = width;
	int cell_size = 5;
	int grid[width][height];
	int next_grid[width][height];
	for(int y = 0 ; y < height ; y++) {
		for(int x = 0 ; x < width ; x++) {
			//grid[x][y] = rand() % 2;i'll just initialize them all dead at the start
			grid[x][y] = 0;
		}
	}
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);
	SetTargetFPS(FPS);
	while(!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLACK);
		//drawing the cells
		for(int y = 0 ; y < height ; y++) {
			for(int x = 0 ; x < width ; x++) {
				int startX = x * cell_size;
				int startY = y * cell_size;
				Color color = (grid[x][y] == 0) ? BLACK : RAYWHITE;
				DrawRectangle(startX, startY, cell_size, cell_size, color);
			}
		}
		if(paused == 0) {
			//refreshing cells
			if(GetTime() >= last_time_refresh) {
				int current_cell;
				int top_left_cell, top_cell, top_right_cell;
				int left_cell;
				int right_cell;
				int bottom_left_cell, bottom_cell, bottom_right_cell;
				int alive_cells = 0;

				for(int y = 0 ; y < height ; y++) {
					for(int x = 0 ; x < width ; x++) {
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
						if(x + 1 < width && y - 1 >= 0) {
							top_right_cell = grid[x + 1][y - 1];
							alive_cells += (top_right_cell == 1) ? 1 : 0;
						}
						//left cell
						if(x - 1 >= 0) {
							left_cell = grid[x-1][y];
							alive_cells += (left_cell == 1) ? 1 : 0;
						}
						//right cell
						if(x + 1 < width) {
							right_cell = grid[x + 1][y];
							alive_cells += (right_cell == 1) ? 1 : 0;
						}
						//bottom left cell
						if(x - 1 >= 0 && y + 1 < height) {
							bottom_left_cell = grid[x - 1][y + 1];
							alive_cells += (bottom_left_cell == 1) ? 1 : 0;
						}
						//bottom cell
						if(y + 1 < height) {
							bottom_cell = grid[x][y + 1];
							alive_cells += (bottom_cell == 1) ? 1 : 0;
						}
						//bottom right cell
						if(x + 1 < width && y + 1 < height) {
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

				for(int y = 0 ; y < height ; y++) {
					for(int x = 0 ; x < width ; x++) {
						grid[x][y] = next_grid[x][y];
					}
				}

				last_time_refresh = GetTime();
			}

		}
		char *game_state = (paused == 1) ? "Paused" : "";
		DrawText(game_state, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 30, RED);
		//randomice simulation
		if(IsKeyPressed(KEY_R)) {
			for(int y = 0 ; y < height ; y++) {
				for(int x = 0 ; x < width ; x++) {
					grid[x][y] = rand() % 2;
					next_grid[x][y] = rand() % 2;
				}
			}
		}
		//clear simulation
		if(IsKeyPressed(KEY_C)) {
			for(int y = 0 ; y < height ; y++) {
				for(int x = 0 ; x < width ; x++) {
					grid[x][y] = 0;
					next_grid[x][y] = 0;
				}
			}
		}
		//functionality related to pausing the simulation
		if(IsKeyPressed(KEY_SPACE)) {
			paused = (paused == 0) ? 1 : 0;
		}
		//this is related to killing or reviving cells with mouse click o_____o
		int mouseX = GetMouseX() / cell_size;
		int mouseY = GetMouseY() / cell_size;
		if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
			grid[mouseX][mouseY] = (grid[mouseX][mouseY] == 0) ? 1 : 0;
			next_grid[mouseX][mouseY] = (grid[mouseX][mouseY] == 0) ? 1 : 0;
		}
		EndDrawing();
	}
	return 0;
}