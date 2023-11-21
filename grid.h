#ifndef GRID_H
#define GRID_H
#include "shapes.h"
#include "score.h"
#include <SDL2/SDL.h>
#include <vector>
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
    char get_grid(int x, int y);
    bool inside_grid(int offset);
    void show_grid();

    bool load_grid_media();
    void render_grid();
    void destroy_line(Score &score_obj);
    bool lose_game();
   
    private:
    char grid[GRID_ROWS][GRID_COLUMNS];
   std::vector<SDL_Texture*> grid_texture;
   std::vector<SDL_Surface*> grid_surface;

};


extern Grid grid_obj;




#endif 