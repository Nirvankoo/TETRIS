#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include"button.h"
#include"run.h"
#include"button_set.h"
#include"shapes.h"
#include"velocity.h"


//objects instances
//**********************************************************************************************************************
int square_shape[4][4] = {
    {1, 1, 0, 0},
    {1, 1, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};

Shape square("square", square_shape, 460, 0); // 460 start position x

int line_shape_[4][4] = {
    {1, 1, 1, 1},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
    };

Shape line("line", line_shape_, 460, 0);





//**********************************************************************************************************************
bool run_flag = false;

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
        //Uint32 delta_time = current_time - last_time;
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                run_flag = true;
            }
            button_start.button_handle_event(&e);
            button_music_switch.button_handle_event(&e);
            button_sound_switch.button_handle_event(&e);
            square.handle_shape_event(&e);
            
        
        }

        

        // Update the object's position
        if(current_time - last_time > 10)
        {
            if(square.inside_grid(0))
            {
            square.set_shape_cord_y(square.get_shape_cord_y() + 1);
            last_time = current_time;
            }
            else
            {
               square.set_shape_cord_x(square.get_shape_cord_x());
               square.set_shape_cord_y(square.get_shape_cord_y());
               
               //populate grid
               int cord_x_temp = square.get_shape_cord_x();
               int cord_y_temp = square.get_shape_cord_y();

               






               last_time = current_time;
            }
        }
        

    
        
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, existing_texture, NULL, NULL);
        button_start.button_render(button_start.button_get_position_x(), button_start.button_get_position_y(), &button_sprite_clips[button_start.button_current_sprite]);

        // button settings !!!!!!!!!!!!!!!!!!!!
        create_button_set(button_music_switch, 10, 10); 
        create_button_set(button_sound_switch, 10, 50);
        // create shapes
        if(start_button)
            {
                create_shapes(square);
            }
       
        



        SDL_RenderPresent(renderer);
    }
}
