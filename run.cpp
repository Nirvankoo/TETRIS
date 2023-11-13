#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "button.h"
#include "run.h"
#include "button_set.h"
#include "shapes.h"
#include "velocity.h"
#include "grid.h"
#include <cmath>
#include "random.h"

// objects instances
//********************************************************************************************************************
Grid grid_obj;
bool run_flag = false;
Shape *current_shape = nullptr;

// next shapes flags
bool next_shape_flag = false;
std::string shape_array[7] = {"square", "line", "T", "L", "Lm", "Z", "Zm"};

void run()
{

    if (!init_button_media())
    {
        std::cout << "Failed to initialize!" << std::endl;
        return;
    }

    SDL_Texture *existing_texture = SDL_CreateTextureFromSurface(renderer, main_window_surface_jpg);
    if (existing_texture == NULL)
    {
        std::cout << "Failed to create texture from surface!" << std::endl;
        destroy_button();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(main_window);
        IMG_Quit();
        SDL_Quit();
        return;
    }

    Uint32 last_time = SDL_GetTicks();
    SDL_Event e;

    while (!run_flag)
    {

        Uint32 current_time = SDL_GetTicks();
        // Uint32 delta_time = current_time - last_time;
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                run_flag = true;
            }
            button_start.button_handle_event(&e);
            button_music_switch.button_handle_event(&e);
            button_sound_switch.button_handle_event(&e);
            current_shape->handle_shape_event(&e);
        }

        // checking if current shape was initialized

        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, existing_texture, NULL, NULL);
        button_start.button_render(button_start.button_get_position_x(), button_start.button_get_position_y(), &button_sprite_clips[button_start.button_current_sprite]);

        // button settings !!!!!!!!!!!!!!!!!!!!
        create_button_set(button_music_switch, 10, 10);
        create_button_set(button_sound_switch, 10, 50);

        // create shapes
        if (start_button && next_shape_flag)
        {
            std::string next_shape_name;
            next_shape_name = pick_rand_shape();
            std::cout << next_shape_name << std::endl;

            current_shape = Shape::create_shapes(next_shape_name);
            if (current_shape == nullptr)
            {
                std::cout << "current shape is null" << std::endl;
            }
      
            // std::cout << current_shape->get_shape_cord_x() << std::endl;
            next_shape_flag = false;
        }

        if (current_shape != nullptr)
        {
            current_shape->render_shape(current_shape->get_shape_cord_x(), current_shape->get_shape_cord_y(), NULL);
            
            
            // std::cerr << "current shape is not null" << std::endl;
            if (current_time - last_time > 10)
            {
                if (current_shape->inside_grid(0))
                {
                    current_shape->set_shape_cord_y(current_shape->get_shape_cord_y() + 1);
                    last_time = current_time;
                }
                else
                {
                    current_shape->set_shape_cord_x(current_shape->get_shape_cord_x());
                    current_shape->set_shape_cord_y(current_shape->get_shape_cord_y());

                    // populate grid
                    int cord_x_temp = current_shape->get_shape_cord_x();
                    int cord_y_temp = current_shape->get_shape_cord_y();

                    if (cord_x_temp >= 300 && cord_x_temp <= 700 && cord_y_temp >= 0 && cord_y_temp <= 800)
                    {
                        int grid_x = std::abs((cord_x_temp - 300) / 40);
                        int grid_y = std::abs(cord_y_temp / 40);

                        grid_obj.set_grid(grid_y, grid_x);

                        std::cout << "grid_x: " << grid_x << std::endl;
                        std::cout << "grid_y: " << grid_y << std::endl;

                        // print current grid
                        // grid_obj.show_grid();
                    }
                    else
                    {
                        std::cout << "Outside grid" << std::endl;
                    }

                    last_time = current_time;
                }
            }
        }

        SDL_RenderPresent(renderer);
    }
}
