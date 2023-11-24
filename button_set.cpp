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



