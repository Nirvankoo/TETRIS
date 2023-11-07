#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "shapes.h"
#include "window.h"
#include "game.h"
#include "button.h"

Shape::Shape()
{
    name = "shape";
    color = {0, 0, 0};
    x = 0;
    y = 0;
}

Shape::Shape(std::string name, SDL_Color color, int shapeType[4][4], int x, int y) : name(name), color(color), x(x), y(y)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            this->shapeType[i][j] = shapeType[i][j];
        }
    }
}

Shape::~Shape()
{
    name = "shape";
    color = {0, 0, 0};
    x = 0;
    y = 0;
}

void Shape::render_shape(int x, int y, SDL_Rect *clip)
{
    int x_offset = 0;
    int y_offset = 0;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {

            if (shapeType[i][j] == 1)
            {
                x = x + x_offset;
                y = y + y_offset;
            }
        }
        SDL_Rect render_quad = {x, y, width, height};
        if (clip != NULL)
        {
            render_quad.w = clip->w;
            render_quad.h = clip->h;
        }
        SDL_RenderCopy(renderer, shape_texture, clip, &render_quad);
    }
}


bool Shape::load_shape_media(std::string path)
{
    bool success = true;
    SDL_Surface *loaded_surface = IMG_Load(path.c_str());
    if (loaded_surface == NULL)
    {
        std::cout << "Unable to load image " << path.c_str() << "! SDL_image Error: " << IMG_GetError() << std::endl;
        success = false;
    }
    else
    {
        SDL_SetColorKey(loaded_surface, SDL_TRUE, SDL_MapRGB(loaded_surface->format, 0, 0xFF, 0xFF));
        shape_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
        if (shape_texture == NULL)
        {
            std::cout << "Unable to create texture from " << path.c_str() << "! SDL Error: " << SDL_GetError() << std::endl;
            success = false;
        }
        else
        {
            width = loaded_surface->w;
            height = loaded_surface->h;
        }
        SDL_FreeSurface(loaded_surface);
    }
    return success;
}

void Shape::handle_shape_event(SDL_Event *e)
{
    bool quit = false;
    while (!quit)
    {
        while (SDL_PollEvent(e) != 0)
        {
            if (e->type == SDL_QUIT)
            {
                quit = true;
            }
            else if (e->type == SDL_KEYDOWN)
            {
                switch (e->key.keysym.sym)
                {
                case SDLK_UP:
                    y -= 10;
                    break;
                case SDLK_DOWN:
                    y += 10;
                    break;
                case SDLK_LEFT:
                    x -= 10;
                    break;
                case SDLK_RIGHT:
                    x += 10;
                    break;
                }
            }
        }
    }
}

void Shape::set_shape_name(std::string name)
{
    this->name = name;
}

void Shape::set_shape_color(SDL_Color color)
{
    this->color = color;
}

void Shape::set_shape_type(int shapeType[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            this->shapeType[i][j] = shapeType[i][j];
        }
    }
}


std::string Shape::get_shape_name()
{
    return name;
}

SDL_Color Shape::get_shape_color()
{
    return color;
}

int Shape::get_shape_x()
{
    return x;
}

int Shape::get_shape_y()
{
    return y;
}







void create_shapes(Shape obj)
{
    if(!(obj.load_shape_media("img/rect.png")))
    {
        std::cout << "Failed to load shape media!" << std::endl;
    }
    
    

   bool quit = false;
   SDL_Event e;

   while(!quit)
   {
       while(SDL_PollEvent(&e) != 0)
       {
           if(e.type == SDL_QUIT)
           {
               quit = true;
           }
           else if(e.type == SDL_KEYDOWN)
           {
               switch(e.key.keysym.sym)
               {
                   case SDLK_UP:{
                   int temp_y = -10;
                   obj.set_shape_position_y(temp_y);
                   break;
                   }
                     case SDLK_DOWN:{
                     int temp_y = 10;
                        obj.set_shape_position_y(temp_y);
                        break;
                     }
                        case SDLK_LEFT:{
                        int temp_x = -10;
                        obj.set_shape_position_x(temp_x);
                        break;
                        }
                            case SDLK_RIGHT:{
                            int temp_x = 10;
                            obj.set_shape_position_x(temp_x);
                            break;
                            }


               }
           }
       }
       obj.render_shape(obj.get_shape_x(), obj.get_shape_y(), NULL);
         SDL_RenderPresent(renderer);
         
   }
}