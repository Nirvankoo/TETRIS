#ifndef BUTTON_SET_H
#define BUTTON_SET_H

#include<SDL2/SDL_ttf.h>
#include"window.h"
#include"game.h"
#include"button.h"

bool intit_button_ttf_font();

void create_button_set(std::string text, int x, int y, SDL_Color color);





#endif