#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "window.h"
#include "game.h"

void create_game(Window_class ob)
{
    if (!init_window(ob))
    {
        std::cout << "Failed to initialize window" << std::endl;
    }
    else
    {
        if(!load_audio())
        {
            std::cout<<"Failed to load audio"<<std::endl;
        }
        main_window_surface = SDL_GetWindowSurface(main_window);
        main_window_surface_jpg = window_load_surface("img/TETRIS.png");
        if(main_window_surface_jpg == NULL)
        {
            std::cout << "Failed to load image " << IMG_GetError() << std::endl;
        }
        else{
            //play music
            Mix_PlayMusic(music, -1);
            
            
            //SDL_Event game_event;
            //bool game_quit = false;
            
            
            /*while (!game_quit)
            {
                while (SDL_PollEvent(&game_event) != 0)
                {
                    

                    if (game_event.type == SDL_KEYDOWN)
                    {
                        game_quit = true;
                    }
                    else if (game_event.type == SDL_QUIT)
                    {
                        exit(0);
                    }
                }
                */
                SDL_BlitSurface(main_window_surface_jpg, NULL, main_window_surface, NULL);
                SDL_UpdateWindowSurface(main_window);
                
        //}
           
        }
    }

}
