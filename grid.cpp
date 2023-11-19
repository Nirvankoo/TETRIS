#include "grid.h"
#include <SDL2/SDL.h>
#include <iostream>








Grid::Grid() {
    for (int i = 0; i <GRID_ROWS; i++) {
        for (int j = 0; j < GRID_COLUMNS; j++) {
            grid[i][j] = false;
        }
    }
}

Grid::~Grid() {
}

void Grid::set_grid(Shape *current_shape)
{
    int shape_type_temp[4][4];

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            shape_type_temp[i][j] = current_shape->get_shape_type(i, j);
        }
    }

    int shape_cord_x = (current_shape->get_shape_cord_x() - GRID_START_X) / 40;
    int shape_cord_y = (current_shape->get_shape_cord_y()) / 40;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (shape_type_temp[i][j] == 1)
            {
                int grid_x = shape_cord_x + j;
                int grid_y = shape_cord_y + i;
                std::cout << "Setting grid[" << grid_y << "][" << grid_x << "] to true." << std::endl;
                // Check if the grid indices are within bounds before setting
                if (grid_x >= 0 && grid_x < GRID_COLUMNS && grid_y >= 0 && grid_y < GRID_ROWS)
                {
                   this->grid[grid_y][grid_x] = true;
                }
            }
        }
    }
}


bool Grid::get_grid(int i, int j) {
    if (i >= 0 && i < GRID_ROWS && j >= 0 && j < GRID_COLUMNS) {
        return grid[i][j];
    }
    return false;
}

void Grid::show_grid() {
    for (int i = 0; i < GRID_ROWS; i++) {
        for (int j = 0; j < GRID_COLUMNS; j++) {
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
     std::cout << std::endl;
}

