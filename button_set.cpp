#include <iostream>
#include <SDL2/SDL_ttf.h>
#include "window.h"
#include "game.h"
#include "button.h"
#include "button_set.h"

bool intit_button_ttf_font()
{
    bool success = true;
    if (TTF_Init() == -1)
    {
        std::cout << "Failed to initialize SDL_ttf! SDL_ttf Error: " << TTF_GetError() << std::endl;
        success = false;
    }
    else
    {
        but_set_font = TTF_OpenFont("Universe.otf", 40);
        if (but_set_font == NULL)
        {
            std::cout << "Failed to load button ttf font! SDL_ttf Error: " << TTF_GetError() << std::endl;
            success = false;
        }
    }
    return success;
}

void create_button_set(Button ob, int x, int y)
{
    SDL_Surface *button_set_surface = TTF_RenderText_Solid(but_set_font, ob.button_name.c_str(), ob.button_color);
    SDL_Texture *button_set_texture = SDL_CreateTextureFromSurface(renderer, button_set_surface);
    SDL_Rect button_set_rect = {x, y, button_set_surface->w, button_set_surface->h};

    SDL_RenderCopy(renderer, button_set_texture, NULL, &button_set_rect);
}