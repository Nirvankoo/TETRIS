#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include "window.h"
#include "game.h"
#include "button.h"
#include "button_set.h"
#include "shapes.h"
#include "run.h"
#include "score.h"

const int BUTTON_WIDTH = 265;
const int BUTTON_HEIGHT = 100;

bool start_button = false;

Button::Button()
{
    button_texture = NULL;
    width = 0;
    height = 0;
    button_position.x = 0;
    button_position.y = 0;
    button_current_sprite = BUTTON_SPRITE_MOUSE_OUT;
}

Button::Button(std::string name, int widht, int height) : button_name(name), width(widht), height(height)
{
    button_color = {0xFF, 0xFF, 0xFF};
    button_texture = NULL;
    button_position.x = 0;
    button_position.y = 0;
    button_current_sprite = BUTTON_SPRITE_MOUSE_OUT;
}

Button::~Button()
{
    button_texture = NULL;
    width = 0;
    height = 0;
    button_position.x = 0;
    button_position.y = 0;
    button_current_sprite = BUTTON_SPRITE_MOUSE_OUT;
    button_texture = NULL;

    button_name = "";
}

bool Button::button_load_media(std::string path)
{
    bool success = true;
    SDL_Surface *loaded_surface = IMG_Load(path.c_str());
    if (loaded_surface == NULL)
    {
        std::cout << "Unable to load image " << path.c_str() << "! SDL_image Error: " << IMG_GetError() << std::endl;
        success = false;
    }
    else
    {
        SDL_SetColorKey(loaded_surface, SDL_TRUE, SDL_MapRGB(loaded_surface->format, 0, 0xFF, 0xFF));
        button_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
        if (button_texture == NULL)
        {
            std::cout << "Unable to create texture from " << path.c_str() << "! SDL Error: " << SDL_GetError() << std::endl;
            success = false;
        }
        SDL_FreeSurface(loaded_surface);
    }
    return success;
}

bool Button::button_load_media_ttf_font()
{
    bool success = true;
    SDL_Surface *button_surface = TTF_RenderText_Solid(but_set_font, button_name.c_str(), button_color);
    if (button_surface == NULL)
    {
        std::cout << "Failed to create button surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
        success = false;
    }
    else
    {
        button_texture = SDL_CreateTextureFromSurface(renderer, button_surface);
        if (button_texture == NULL)
        {
            std::cout << "Failed to create button texture! SDL_ttf Error: " << TTF_GetError() << std::endl;
            success = false;
        }
        else
        {
            width = button_surface->w;
            height = button_surface->h;
        }
        SDL_FreeSurface(button_surface);
    }
    return success;
}

void Button::button_render_ttf_font(int x, int y, SDL_Rect *clip)
{
    SDL_Rect button_set_rect = {x, y, width, height};
    SDL_RenderCopy(renderer, button_texture, clip, &button_set_rect);
}

void Button::button_render(int x, int y, SDL_Rect *clip)
{
    SDL_Rect render_quad = {x, y, width, height};
    if (clip != NULL)
    {
        render_quad.w = clip->w;
        render_quad.h = clip->h;
    }
    SDL_RenderCopy(renderer, button_texture, clip, &render_quad);
}

int Button::button_get_width()
{
    return width;
}

int Button::button_get_height()
{
    return height;
}

void Button::button_set_position(int x, int y)
{
    button_position.x = x;
    button_position.y = y;
}

int Button::button_get_position_x()
{
    return button_position.x;
}

int Button::button_get_position_y()
{
    return button_position.y;
}

void Button::button_handle_event(SDL_Event *e)
{
    if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        bool inside = true;

        if (x < button_position.x || x > button_position.x + width ||
            y < button_position.y || y > button_position.y + height)
        {
            inside = false;
        }

        if (!inside)
        {
            button_current_sprite = BUTTON_SPRITE_MOUSE_OUT;
            button_color = {0xFF, 0xFF, 0xFF};
        }
        else
        {
            switch (e->type)
            {
            case SDL_MOUSEMOTION:
                button_current_sprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                std::cout << "<MOUSE OVER " << button_name << ">"
                          << "x:" << x << "y:" << y << std::endl;
                button_color = {0xFF, 0xFF, 0x00};
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (button_name == "start")
                {
                    // Handle action for the START button
                    button_current_sprite = BUTTON_SPRITE_MOUSE_DOWN;
                    if (sound_effect)
                    {
                        Mix_PlayChannel(-1, button_click, 0);
                    }
                    destroy_button();
                    start_button = true;
                    next_shape_flag = true;
                    //*******************************************************************
                    // reset position of the square that it appers at the top of the screen

                    return;
                }
                else if (button_name == "MUSIC : ON" || button_name == "MUSIC : OFF")
                {
                    if (button_name == "MUSIC : ON")
                    {
                         button_set_name("MUSIC : OFF");
                        // Handle action for the MUSIC button
                        SDL_Surface *button_surface = TTF_RenderText_Solid(but_set_font, button_name.c_str(), button_color);
                        button_texture = SDL_CreateTextureFromSurface(renderer, button_surface);
                        SDL_FreeSurface(button_surface);
                        
                        Mix_PlayChannel(-1, button_click, 0);
                       
                        Mix_PauseMusic();
                    }
                    else if (button_name == "MUSIC : OFF")
                    {
                        button_set_name("MUSIC : ON");
                        SDL_Surface *button_surface = TTF_RenderText_Solid(but_set_font, button_name.c_str(), button_color);
                        button_texture = SDL_CreateTextureFromSurface(renderer, button_surface);
                        SDL_FreeSurface(button_surface);
                        Mix_PlayChannel(-1, button_click, 0);
                        
                        Mix_ResumeMusic();
                    }
                }
                else if (button_name == "SOUND : ON" || button_name == "SOUND : OFF")
                {
                    if (button_name == "SOUND : ON")
                    {
                        button_set_name("SOUND : OFF");
                        SDL_Surface *button_surface = TTF_RenderText_Solid(but_set_font, button_name.c_str(), button_color);
                        button_texture = SDL_CreateTextureFromSurface(renderer, button_surface);
                        SDL_FreeSurface(button_surface);
                        // Handle action for the SOUND button
                        Mix_PlayChannel(-1, button_click, 0);
                        
                        sound_effect = false;
                    }
                    else if (button_name == "SOUND : OFF")
                    {
                         button_set_name("SOUND : ON");
                        SDL_Surface *button_surface = TTF_RenderText_Solid(but_set_font, button_name.c_str(), button_color);
                        button_texture = SDL_CreateTextureFromSurface(renderer, button_surface);
                        SDL_FreeSurface(button_surface);
                        Mix_PlayChannel(-1, button_click, 0);
                       
                        sound_effect = true;
                    }
                }
                break;
            }
        }
    }
}

void Button::button_set_name(std::string name)
{
    button_name = name;
}

// buttons objects!!!!!!!!!!!!!!!!!!!

Button button_start("start", 265, 100);
SDL_Rect button_sprite_clips[BUTTON_SPRITE_TOTAL];
Button button_music_switch("MUSIC : ON", 10, 10);
Button button_sound_switch("SOUND : ON", 10, 50);
Score score_obj(800, 50, 800, 100);

bool init_button()
{
    bool success = true;
    button_start = Button();

    return success;
}

bool init_button_media()
{
    bool succes = true;
    if (!button_start.button_load_media("img/start.png"))
    {
        std::cout << "Failed to load button media!" << std::endl;
        succes = false;
    }
    else if (!(intit_button_ttf_font()))
    {
        std::cout << "Failed to load button ttf font!" << std::endl;
        succes = false;
    }

    for (int i = 0; i < BUTTON_SPRITE_TOTAL; ++i)
    {
        button_sprite_clips[i].x = 0;
        button_sprite_clips[i].y = i * 100;
        button_sprite_clips[i].w = button_start.button_get_width();
        button_sprite_clips[i].h = button_start.button_get_height();
    }

    button_start.button_set_position(355, 345);
    button_music_switch.button_set_position(10, 10);
    button_sound_switch.button_set_position(10, 50);
    button_music_switch.button_load_media_ttf_font();
    button_sound_switch.button_load_media_ttf_font();
    

    return succes;
}

void destroy_button()
{
    button_start.~Button();
}

bool init_button_madia_ttf_font()
{
    bool success = true;
    if (!button_music_switch.button_load_media_ttf_font())
    {
        std::cout << "Failed to load button media!" << std::endl;
        success = false;
    }
    else if (!button_sound_switch.button_load_media_ttf_font())
    {
        std::cout << "Failed to load button media!" << std::endl;
        success = false;
    }
    return success;
}
