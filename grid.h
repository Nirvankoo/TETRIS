#ifndef GRID_H
#define GRID_H
#include "shapes.h"
//      int x =400
// __________
// |        |
// |        |
// |        | int y = 800
// |        |
// |________|

//step  x = 10
//step  y = 20
#define GRID_ROWS 20
#define GRID_COLUMNS 10
#define GRID_START_X 300
#define GRID_START_Y 0


class Grid
{
    public:
    Grid();
    ~Grid();
    void set_grid(Shape *current_shape);
    bool get_grid(int x, int y);
    bool inside_grid(int offset);
    void show_grid();
    
    private:
    bool grid[GRID_ROWS][GRID_COLUMNS];

};


extern Grid grid_obj;




#endif 