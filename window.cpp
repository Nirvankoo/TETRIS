#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "window.h"

bool sound_effect = true;
SDL_Window *main_window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Surface *main_window_surface = NULL;
SDL_Surface *main_window_surface_jpg = NULL;


Mix_Music *music = NULL;
Mix_Chunk *button_click = NULL;
Mix_Chunk *button_hover = NULL;

TTF_Font *but_set_font = NULL;
SDL_Color but_set_color = {0, 0, 0};


Window_class::Window_class()
{
    height = 0;
    width = 0;
}

Window_class::Window_class(int x, int y)
{
    height = x;
    width = y;
}



int Window_class::get_window_height()
{
    return height;
}

int Window_class::get_window_width()
{
    return width;
}

SDL_Surface *window_load_surface(const std::string &path)
{
    SDL_Surface *optimized_surface = NULL;
    SDL_Surface *loaded_surface = IMG_Load(path.c_str());
    if (loaded_surface == NULL)
    {
        std::cout << "Unable to load image " << path.c_str() << "! SDL_image Error: " << IMG_GetError() << std::endl;
    }
    else
    {
        optimized_surface = SDL_ConvertSurface(loaded_surface, main_window_surface->format, 0);
        if (optimized_surface == NULL)
        {
            std::cout << "Unable to optimize image " << path.c_str() << "! SDL Error: " << SDL_GetError() << std::endl;
        }
        SDL_FreeSurface(loaded_surface);
    }
    return optimized_surface;
}

bool init_window(Window_class window_class)
{
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        success = false;
    }
    else
    {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
        }
        main_window = SDL_CreateWindow("TETRIS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_class.get_window_width(), window_class.get_window_height(), SDL_WINDOW_SHOWN);
        if (main_window == NULL)
        {
            std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
            success = false;
        }
        else
        {
            renderer = SDL_CreateRenderer(main_window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer == NULL)
            {
                std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
                    success = false;
                }
                if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
                {
                    std::cout<<"SDL_mixer could not initialize! SDL_mixer Error: "<<Mix_GetError()<<std::endl;
                    success = false;
                }
            }
        }
    }
    

    return success;
}

bool load_audio()
{
   bool succes = true;

   music = Mix_LoadMUS("audio/music.wav");
   if(music == NULL)
   {
       std::cout<<"Failed to load music! SDL_mixer Error: "<<Mix_GetError()<<std::endl;
       succes = false;
   }

    button_click = Mix_LoadWAV("audio/button_click.wav");
    if(button_click == NULL)
    {
        std::cout<<"Failed to load button click sound effect! SDL_mixer Error: "<<Mix_GetError()<<std::endl;
        succes = false;
    }
    return succes;
}

void close_window()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(main_window);
    main_window = NULL;
    renderer = NULL;
    Mix_FreeChunk(button_click);
    Mix_FreeMusic(music);
    button_click = NULL;
    music = NULL;
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}