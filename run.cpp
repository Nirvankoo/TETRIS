 
 #include "run.h"
 #include "button.h"
    #include "window.h"
    #include "game.h"
    #include "button_set.h"
    #include "shapes.h"
    #include <iostream>
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
    #include <SDL2/SDL_mixer.h>
    #include <string>
    


 void run(){
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

    
    SDL_Event e;

    while (!quit_start)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit_start = true;
            }
            button_start.button_handle_event(&e);
            button_music_switch.button_handle_event(&e);
            button_sound_switch.button_handle_event(&e);
        }
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, existing_texture, NULL, NULL);
        button_start.button_render(button_start.button_get_position_x(), button_start.button_get_position_y(), &button_sprite_clips[button_start.button_current_sprite]);

        // button settings !!!!!!!!!!!!!!!!!!!!
        create_button_set(button_music_switch, 10, 10); 
        create_button_set(button_sound_switch, 10, 50);

        SDL_RenderPresent(renderer);
    }
 }