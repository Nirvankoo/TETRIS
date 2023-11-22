#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include"window.h"
#include"game.h"
#include"button.h"
#include"button_set.h"
#include"score.h"


Score::Score()
{
    score = 0;
    level = 1;
}

Score::~Score()
{
    score = 0;
    level = 0;
}

void Score::set_score(int score)
{
    this->score = score;
}

void Score::set_level()
{ 

    if((this->score < 1000))
    this->level = 1;
    else if(this->score < 2000)
    this->level = 2;
    else if(this->score < 3000)
    this->level = 3;
    else if(this->score < 4000)
    this->level = 4;
    else if(this->score < 5000)
    this->level = 5;
    else if(this->score < 6000)
    this->level = 6;
    else if(this->score < 7000)
    this->level = 7;
    else if(this->score < 8000)
    this->level = 8;
    else if(this->score < 9000)
    this->level = 9;
    else if(this->score < 10000)
    this->level = 10;
    else if(this->score < 11000)
    this->level = 11;

}

int Score::get_score()
{
    return score;
}

int Score::get_level()
{
    return level;
}

void Score::show_score_on_screen(int x, int y)
{
    std::string score_str = "Score:" + std::to_string(score);
    std::string level_str = "Level:" + std::to_string(level);
    SDL_Surface *level_surface = TTF_RenderText_Solid(but_set_font, level_str.c_str(), {255, 255, 255});
    SDL_Surface *score_surface = TTF_RenderText_Solid(but_set_font, score_str.c_str(), {255, 255, 255});
    SDL_Texture *score_texture = SDL_CreateTextureFromSurface(renderer, score_surface);
    SDL_Texture *level_texture = SDL_CreateTextureFromSurface(renderer, level_surface);
    SDL_Rect score_rect = {x, y, score_surface->w, score_surface->h};
    SDL_Rect level_rect = {x, y + 50, level_surface->w, level_surface->h};
    SDL_RenderCopy(renderer, score_texture, NULL, &score_rect);
    SDL_RenderCopy(renderer, level_texture, NULL, &level_rect);
}