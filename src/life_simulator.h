#include <stdlib.h>
#include <time.h>
#include "raylib.h"
#define FPS           60
#define SCREEN_WIDTH  1280
#define SCREEN_HEIGHT 640
#define TITLE         "Life Simulator"
#define GRID_WIDTH    300
#define GRID_HEIGHT   GRID_WIDTH
void initialize_cells(int grid[GRID_WIDTH][GRID_HEIGHT]);
void draw_cells(int grid[GRID_WIDTH][GRID_HEIGHT], int cell_size);
void calculate_next_cell_generation(int grid[GRID_WIDTH][GRID_HEIGHT], int next_grid[GRID_WIDTH][GRID_HEIGHT], int seconds_between_each_generation, double *last_time_refresh);
void pause_simulation(int *paused);
void randomice_simulation(int grid[GRID_WIDTH][GRID_HEIGHT], int next_grid[GRID_WIDTH][GRID_HEIGHT]);
void clear_simulation(int grid[GRID_WIDTH][GRID_HEIGHT], int next_grid[GRID_WIDTH][GRID_HEIGHT]);
void kill_or_revive_cell(int grid[GRID_WIDTH][GRID_HEIGHT], int next_grid[GRID_WIDTH][GRID_HEIGHT], int cell_size);
void draw_simulation_state(char *simulation_state, int paused);