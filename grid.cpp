#include "grid.h"
#include <SDL2/SDL.h>
#include <iostream>

const int cell_width = 40;
const int cell_height = 40;
const int grid_rows = 20;
const int grid_columns = 10;

const int start_x = 300;
const int start_y = 0;




Grid::Grid() {
    for (int i = 0; i < grid_rows; i++) {
        for (int j = 0; j < grid_columns; j++) {
            grid[i][j] = false;
        }
    }
}

Grid::~Grid() {
}

void Grid::set_grid(int x, int y) {
    int i = x;
    int j = y;

    
        grid[i][j] = true;
    
}


bool Grid::get_grid(int i, int j) {
    if (i >= 0 && i < grid_rows && j >= 0 && j < grid_columns) {
        return grid[i][j];
    }
    return false;
}

void Grid::show_grid() {
    for (int i = 0; i < grid_rows; i++) {
        for (int j = 0; j < grid_columns; j++) {
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
     std::cout << std::endl;
}

