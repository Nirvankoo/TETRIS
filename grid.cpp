#include "grid.h"
#include <SDL2/SDL.h>
#include <iostream>

const int cell_width = 40;
const int cell_height = 40;
const int grid_rows = 10;
const int grid_columns = 20;

const int start_x = 300;
const int start_y = 0;

SDL_Rect grid_cord[grid_rows][grid_columns];

void init_grid() {
    for (int row = 0; row < grid_rows; row++) {
        for (int column = 0; column < grid_columns; column++) {
            SDL_Rect cell_rect;
            cell_rect.x = start_x + column * cell_width;
            cell_rect.y = start_y + row * cell_height;
            cell_rect.w = cell_width;
            cell_rect.h = cell_height;
            grid_cord[row][column] = cell_rect;
        }
    }
}

Grid::Grid() {
    for (int i = 0; i < grid_rows; i++) {
        for (int j = 0; j < grid_columns; j++) {
            grid[i][j] = 0;
        }
    }
}

Grid::~Grid() {
}

void Grid::set_grid(int i, int j) {
    if (i >= 0 && i < grid_rows && j >= 0 && j < grid_columns) {
        grid[i][j] = 1;
    }
}

bool Grid::get_grid(int i, int j) {
    if (i >= 0 && i < grid_rows && j >= 0 && j < grid_columns) {
        return grid[i][j];
    }
    return false;
}
