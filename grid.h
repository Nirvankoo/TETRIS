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


class Grid
{
    public:
    Grid();
    ~Grid();
    void set_grid(int x, int y);
    bool get_grid(int x, int y);
    bool inside_grid(int offset);
    void show_grid();
    
    private:
    bool grid[10][20];

};

void init_grid();
extern Grid grid_obj;




#endif 