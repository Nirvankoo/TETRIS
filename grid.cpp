#include "grid.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <SDL2/SDL_image.h>
#include"window.h"

Grid::Grid()
{
    for (int i = 0; i < GRID_ROWS; i++)
    {
        for (int j = 0; j < GRID_COLUMNS; j++)
        {
            grid[i][j] = '*';
        }
    }
    std::vector<SDL_Texture*> grid_texture;
    std::vector<SDL_Surface*> grid_surface;
    

}

Grid::~Grid()
{
   
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
                    if (current_shape->get_shape_name() == "Square")
                    {
                        grid[grid_y][grid_x] = 'S';
                    }
                    else if (current_shape->get_shape_name() == "Line")
                    {
                        grid[grid_y][grid_x] = 'L';
                    }
                    else if (current_shape->get_shape_name() == "T")
                    {
                        grid[grid_y][grid_x] = 'T';
                    }
                    else if (current_shape->get_shape_name() == "L")
                    {
                        grid[grid_y][grid_x] = 'P';
                    }
                    else if (current_shape->get_shape_name() == "Lm")
                    {
                        grid[grid_y][grid_x] = 'P';
                    }
                    else if (current_shape->get_shape_name() == "Z")
                    {
                        grid[grid_y][grid_x] = 'Z';
                    }
                    else if (current_shape->get_shape_name() == "Zm")
                    {
                        grid[grid_y][grid_x] = 'Z';
                    }
                }
            }
        }
    }
}

char Grid::get_grid(int i, int j)
{
    return grid[i][j];
    
}

void Grid::show_grid()
{
    for (int i = 0; i < GRID_ROWS; i++)
    {
        for (int j = 0; j < GRID_COLUMNS; j++)
        {
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

bool Grid::load_grid_media()
{
    bool success = true;
    SDL_Surface *loaded_surface = IMG_Load("img/rect.png");
    if(loaded_surface == NULL)
    {
        std::cout << "Unable to load image " << "img/rect.png" << "! SDL_image Error: " << IMG_GetError() << std::endl;
        success = false;
    }
    else
    {
        SDL_SetColorKey(loaded_surface, SDL_TRUE, SDL_MapRGB(loaded_surface->format, 0, 0xFF, 0xFF));
        SDL_Texture *square_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
        if(square_texture == NULL)
        {
            std::cout << "Unable to create texture from " << "img/square.png" << "! SDL Error: " << SDL_GetError() << std::endl;
            success = false;
        }
        grid_texture.push_back(square_texture);
        SDL_FreeSurface(loaded_surface);

    }

    loaded_surface = IMG_Load("img/line.png");
    if(loaded_surface == NULL)
    {
        std::cout << "Unable to load image " << "img/line.png" << "! SDL_image Error: " << IMG_GetError() << std::endl;
        success = false;
    }
    else
    {
        SDL_SetColorKey(loaded_surface, SDL_TRUE, SDL_MapRGB(loaded_surface->format, 0, 0xFF, 0xFF));
        SDL_Texture *line_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
        if(line_texture == NULL)
        {
            std::cout << "Unable to create texture from " << "img/line.png" << "! SDL Error: " << SDL_GetError() << std::endl;
            success = false;
        }
        grid_texture.push_back(line_texture);
        SDL_FreeSurface(loaded_surface);

    }

    loaded_surface = IMG_Load("img/T.png");
    if(loaded_surface == NULL)
    {
        std::cout << "Unable to load image " << "img/T.png" << "! SDL_image Error: " << IMG_GetError() << std::endl;
        success = false;
    }
    else
    {
        SDL_SetColorKey(loaded_surface, SDL_TRUE, SDL_MapRGB(loaded_surface->format, 0, 0xFF, 0xFF));
        SDL_Texture *T_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
        if(T_texture == NULL)
        {
            std::cout << "Unable to create texture from " << "img/T.png" << "! SDL Error: " << SDL_GetError() << std::endl;
            success = false;
        }
        grid_texture.push_back(T_texture);
        SDL_FreeSurface(loaded_surface);

    }

    loaded_surface = IMG_Load("img/L.png");
    if(loaded_surface == NULL)
    {
        std::cout << "Unable to load image " << "img/L.png" << "! SDL_image Error: " << IMG_GetError() << std::endl;
        success = false;
    }
    else
    {
        SDL_SetColorKey(loaded_surface, SDL_TRUE, SDL_MapRGB(loaded_surface->format, 0, 0xFF, 0xFF));
        SDL_Texture *L_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
        if(L_texture == NULL)
        {
            std::cout << "Unable to create texture from " << "img/L.png" << "! SDL Error: " << SDL_GetError() << std::endl;
            success = false;
        }
        grid_texture.push_back(L_texture);
        SDL_FreeSurface(loaded_surface);

    }

    loaded_surface = IMG_Load("img/Z.png");
    if(loaded_surface == NULL)
    {
        std::cout << "Unable to load image " << "img/Z.png" << "! SDL_image Error: " << IMG_GetError() << std::endl;
        success = false;
    }
    else
    {
        SDL_SetColorKey(loaded_surface, SDL_TRUE, SDL_MapRGB(loaded_surface->format, 0, 0xFF, 0xFF));
        SDL_Texture *Z_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
        if(Z_texture == NULL)
        {
            std::cout << "Unable to create texture from " << "img/Z.png" << "! SDL Error: " << SDL_GetError() << std::endl;
            success = false;
        }
        grid_texture.push_back(Z_texture);
        SDL_FreeSurface(loaded_surface);

    }
    return success;
}

void Grid::render_grid()
{
   for(int i = 0; i < GRID_ROWS; i++)
   {
       for(int j = 0; j < GRID_COLUMNS; j++)
       {
           if(grid[i][j] == 'S')
           {
               SDL_Rect render_quad = {GRID_START_X + j * 40, i * 40, 40, 40};
               SDL_RenderCopy(renderer, grid_texture[0], NULL, &render_quad);
           }
           else if(grid[i][j] == 'L')
           {
               SDL_Rect render_quad = {GRID_START_X + j * 40, i * 40, 40, 40};
               SDL_RenderCopy(renderer, grid_texture[1], NULL, &render_quad);
           }
           else if(grid[i][j] == 'T')
           {
               SDL_Rect render_quad = {GRID_START_X + j * 40, i * 40, 40, 40};
               SDL_RenderCopy(renderer, grid_texture[2], NULL, &render_quad);
           }
           else if(grid[i][j] == 'P')
           {
               SDL_Rect render_quad = {GRID_START_X + j * 40, i * 40, 40, 40};
               SDL_RenderCopy(renderer, grid_texture[3], NULL, &render_quad);
           }
           else if(grid[i][j] == 'Z')
           {
               SDL_Rect render_quad = {GRID_START_X + j * 40, i * 40, 40, 40};
               SDL_RenderCopy(renderer, grid_texture[4], NULL, &render_quad);
           }
       }
   }
}

