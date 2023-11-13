#include "shapes.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "window.h"
#include "grid.h"

int const workspace_x1 = 300;
int const workspace_y1 = 0;
int const workspace_x2 = 640;
int const workspacey_2 = 720;

Shape::Shape()
{
    shape_texture = NULL;
    name = "";
    shape_color = {0xFF, 0xFF, 0xFF};
    cord_x = 460;
    cord_y = 0;
}

Shape::Shape(std::string name, int cord_x, int cord_y) : name(name), cord_x(cord_x), cord_y(cord_y)
{
    shape_texture = NULL;
    shape_color = {0xFF, 0xFF, 0xFF};
}

Shape::~Shape()
{
    shape_texture = NULL;
    name = "";
    shape_color = {0xFF, 0xFF, 0xFF};
    cord_x = 0;
    cord_y = 0;
}

void Shape::render_shape(int x, int y, SDL_Rect *clip)
{
    int x_offset = 40;
    int y_offset = 40;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (shape_type[i][j] == 1)
            {
                // Calculate the render position based on the offsets
                int render_x = x + i * x_offset;
                int render_y = y + j * y_offset;

                SDL_Rect render_quad = {render_x, render_y, shape_width, shape_width};
                if (clip != NULL)
                {
                    render_quad.w = clip->w;
                    render_quad.h = clip->h;
                }
                SDL_RenderCopy(renderer, this->shape_texture, clip, &render_quad);
            }
        }
    }
}


    bool Shape::load_shape_media(std::string path)
    {
        bool success = true;
        SDL_Surface *loaded_surface = IMG_Load(path.c_str());
        if (loaded_surface == NULL)
        {
            std::cout << "Unable to load image" << path.c_str() << "! SDL_image Error: " << IMG_GetError() << std::endl;
            success = false;
        }
        else
        {
            SDL_SetColorKey(loaded_surface, SDL_TRUE, SDL_MapRGB(loaded_surface->format, 0, 0xFF, 0xFF));
            this->shape_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
            if (this->shape_texture == NULL)
            {
                std::cout << "Unable to create texture from " << path.c_str() << "! SDL Error: " << SDL_GetError() << std::endl;
                success = false;
            }
            else
            {
                this->shape_width = loaded_surface->w;
                this->shape_height = loaded_surface->h;
            }
            SDL_FreeSurface(loaded_surface);
        }
        return success;
    }

    void Shape::handle_shape_event(SDL_Event * e)
    {

        if (e->type == SDL_QUIT)
        {
            // Handle quit event
        }
        else if (e->type == SDL_KEYDOWN)
        {
            switch (e->key.keysym.sym)
            {
            case SDLK_LEFT:
            {
                int temp_x = -40;
                if (this->inside_grid(temp_x))
                {
                    this->set_shape_cord_x(this->get_shape_cord_x() + temp_x);
                }
                else
                {
                    std::cout << "Outside grid" << std::endl;
                }

                break;
            }
            case SDLK_RIGHT:
            {
                int temp_x = 40;
                if (this->inside_grid(temp_x))
                {
                    this->set_shape_cord_x(this->get_shape_cord_x() + temp_x);
                }
                else
                {
                    std::cout << "Outside grid" << std::endl;
                }
                break;
            }
            }
        }
    }

    void Shape::set_shape_name(std::string name)
    {
        this->name = name;
    }

    void Shape::set_shape_color(SDL_Color shape_color)
    {
        this->shape_color = shape_color;
    }

    void Shape::set_shape_type(int shape_type[4][4])
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                this->shape_type[i][j] = shape_type[i][j];
            }
        }
    }

    void Shape::set_shape_cord_x(int cord_x)
    {
        this->cord_x = cord_x;
    }

    void Shape::set_shape_cord_y(int cord_y)
    {
        this->cord_y = cord_y;
    }

    void Shape::set_shape_width(int shape_width)
    {
        this->shape_width = shape_width;
    }

    void Shape::set_shape_height(int shape_height)
    {
        this->shape_height = shape_height;
    }

    std::string Shape::get_shape_name()
    {
        return this->name;
    }

    SDL_Color Shape::get_shape_color()
    {
        return this->shape_color;
    }

    int Shape::get_shape_type(int i, int j)
    {
        return this->shape_type[i][j];
    }

    int Shape::get_shape_cord_x()
    {
        return this->cord_x;
    }

    int Shape::get_shape_cord_y()
    {
        return this->cord_y;
    }

    int Shape::get_shape_width()
    {
        return this->shape_width;
    }

    int Shape::get_shape_height()
    {
        return this->shape_height;
    }

    // miscilaneous

    bool Shape::inside_grid(int offset)
    {
        bool inside_grid_flag = true;
        int temp_x = this->get_shape_cord_x() + offset;
        int temp_y = this->get_shape_cord_y();
        // seting gorizontal limits according to edges of the working area
        {
            if (temp_x < workspace_x1 || temp_x > workspace_x2 || temp_y < workspace_y1 || temp_y > workspacey_2)
                inside_grid_flag = false;
        }
        return inside_grid_flag;
    }

    /*void create_shapes(Shape &obj)
    {
        if (!(obj.load_shape_media("img/rect.png")))
        {
            std::cout << "Failed to load shape media" << std::endl;
        }
        else
        {
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    if (obj.get_shape_type(i, j) == 1)
                    {
                        obj.render_shape(obj.get_shape_cord_x() + i * 40, obj.get_shape_cord_y() + j * 40, NULL);
                    }
                }
            }
            SDL_RenderPresent(renderer);
        }
    }
    */
    Shape *Shape::create_shapes(const std::string &name)
    {
        Shape *new_shape_obj = nullptr;

        if (name == "square")
        {
            new_shape_obj = new Square();
            if (!new_shape_obj->load_shape_media("img/rect.png"))
            {
                std::cout << "Failed to load shape media" << std::endl;
            }
        }
        else if (name == "line")
        {
            new_shape_obj = new Line();
            if (!new_shape_obj->load_shape_media("img/line.png"))
            {
                std::cout << "Failed to load shape media" << std::endl;
            }
        }
        else if (name == "T")
        {
            new_shape_obj = new T();
            if (!new_shape_obj->load_shape_media("img/T.png"))
            {
                std::cout << "Failed to load shape media" << std::endl;
            }
        }
        else if (name == "L")
        {
            new_shape_obj = new L();
            if (!new_shape_obj->load_shape_media("img/L.png"))
            {
                std::cout << "Failed to load shape media" << std::endl;
            }
        }
        else if (name == "Lm")
        {
            new_shape_obj = new Lm();
            if (!new_shape_obj->load_shape_media("img/Lm.png"))
            {
                std::cout << "Failed to load shape media" << std::endl;
            }
        }
        else if (name == "Z")
        {
            new_shape_obj = new Z();
            if (!new_shape_obj->load_shape_media("img/Z.png"))
            {
                std::cout << "Failed to load shape media" << std::endl;
            }
        }
        else if (name == "Zm")
        {
            new_shape_obj = new Zm();
            if (!new_shape_obj->load_shape_media("img/Zm.png"))
            {
                std::cout << "Failed to load shape media" << std::endl;
            }
        }
        else
        {
            std::cout << "Invalid shape name" << std::endl;
        }
        return new_shape_obj;
        new_shape_obj = nullptr;
    }
