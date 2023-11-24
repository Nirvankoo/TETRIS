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
    score_position.x = 0;
    score_position.y = 0;
    level_position.x = 0;
    level_position.y = 0;
    score_texture = NULL;
    level_texture = NULL;
    score_width = 0;
    score_height = 0;
    level_width = 0;
    level_height = 0;

}

Score::Score(int score_x, int score_y, int level_x, int level_y) : score_position({score_x, score_y}), level_position({level_x, level_y})
{
    score = 0;
    level = 1;
    score_texture = NULL;
    level_texture = NULL;
    score_width = 0;
    score_height = 0;
    level_width = 0;
    level_height = 0;
}


Score::~Score()
{
    score = 0;
    level = 0;
    score_position.x = 0;
    score_position.y = 0;
    level_position.x = 0;
    level_position.y = 0;
    score_texture = NULL;
    level_texture = NULL;
    score_width = 0;
    score_height = 0;
    level_width = 0;
    level_height = 0;
    

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

void Score::set_score_position(int x, int y)
{
    score_position.x = x;
    score_position.y = y;
}

void Score::set_level_position(int x, int y)
{
    level_position.x = x;
    level_position.y = y;
}

int Score::get_score()
{
    return score;
}

int Score::get_level()
{
    return level;
}

int Score::get_score_position_x()
{
    return score_position.x;
}

int Score::get_score_position_y()
{
    return score_position.y;
}

int Score::get_level_position_x()
{
    return level_position.x;
}

int Score::get_level_position_y()
{
    return level_position.y;
}




bool Score::load_score_media()
{
    bool success = true;
    std::string score_str = "Score:" + std::to_string(score);
    std::string level_str = "Level:" + std::to_string(level);
    
    SDL_Surface *score_surface = TTF_RenderText_Solid(but_set_font, score_str.c_str(), {255, 255, 255});
    SDL_Surface *level_surface = TTF_RenderText_Solid(but_set_font, level_str.c_str(), {255, 255, 255});
    score_texture = SDL_CreateTextureFromSurface(renderer, score_surface);
    if(score_texture == NULL)
    {
        std::cout << "Failed to create texture from surface!" << std::endl;
       success = false;
    }
    else
    {
        score_width = score_surface->w;
        score_height = score_surface->h;
    }

    level_texture = SDL_CreateTextureFromSurface(renderer, level_surface);
    if(level_texture == NULL)
    {
        std::cout << "Failed to create texture from surface!" << std::endl;
        success = false;
    }
    else
    {
        level_width = score_surface->w;
        level_height = score_surface->h;
    }
    SDL_FreeSurface(score_surface);
    SDL_FreeSurface(level_surface);
    return success;
}    

void Score::render_score(int x, int y, SDL_Rect *clip)
{
    if(clip != NULL)
    {
        score_width = clip->w;
        score_height = clip->h;
        level_width = clip->w;
        level_height = clip->h;
    }
    SDL_Rect score_rect = {x, y, score_width, score_height};
    SDL_Rect level_rect = {x, y + 50, level_width, level_height};
    SDL_RenderCopy(renderer, score_texture, clip, &score_rect);
    SDL_RenderCopy(renderer, level_texture,clip, &level_rect);

}

bool init_score_media()
{
        bool success = true;
        if(!score_obj.load_score_media())
        {
            std::cout << "Failed to load score media!" << std::endl;
            return false;
        }

        score_obj.set_score_position(800, 50);
        score_obj.set_level_position(800, 50);
        

    return success;
}

void update_score()
{
    score_obj.load_score_media();
}