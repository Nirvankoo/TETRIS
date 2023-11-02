#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>
#include<string>
#include"window.h"
#include"game.h"
#include"button.h"
#include"button_set.h"

const int BUTTON_WIDTH = 265;
const int BUTTON_HEIGHT = 100;

Button::Button()
{
    button_texture = NULL;
    width = 0;
    height = 0;
    button_position.x = 0;
    button_position.y = 0;
    button_current_sprite = BUTTON_SPRITE_MOUSE_OUT;
}

Button::Button(int x, int y, int widht, int height)
{
    button_texture = NULL;
    width = widht;
    height = height;
    button_position.x = x;
    button_position.y = y;
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
}

bool Button::button_load_media(std::string path)
{
    bool success = true;
    SDL_Surface *loaded_surface = IMG_Load(path.c_str());
    if(loaded_surface == NULL)
    {
        std::cout<<"Unable to load image "<<path.c_str()<<"! SDL_image Error: "<<IMG_GetError()<<std::endl;
        success = false;
    }
    else
    {
        SDL_SetColorKey(loaded_surface, SDL_TRUE, SDL_MapRGB(loaded_surface->format, 0, 0xFF, 0xFF));
        button_texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);
        if(button_texture == NULL)
        {
            std::cout<<"Unable to create texture from "<<path.c_str()<<"! SDL Error: "<<SDL_GetError()<<std::endl;
            success = false;
        }
        else
        {
            width = loaded_surface->w;
            height = loaded_surface->h;
        }
        SDL_FreeSurface(loaded_surface);
    }
    return success;
}

void Button::button_render(int x, int y, SDL_Rect* clip)
{
SDL_Rect render_quad = {x, y, width, height};
if(clip != NULL)
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

int Button::button_get_position_x(){
    return button_position.x;
}

int Button::button_get_position_y(){
    return button_position.y;
}


void Button::button_handle_event(SDL_Event *e)
{
   if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        bool inside = true;

        if (x < button_position.x)
        {
            inside = false;
        }
        else if (x > button_position.x + BUTTON_WIDTH)
        {
            inside = false;
        }
        else if (y < button_position.y)
        {
            inside = false;
        }
        else if (y > button_position.y + BUTTON_HEIGHT)
        {
            inside = false;
        }
        if (!inside)
        {
            button_current_sprite = BUTTON_SPRITE_MOUSE_OUT;
        }
        else
        {
            switch (e->type)
            {
            
            case SDL_MOUSEMOTION:
                button_current_sprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                std::cout<<"<MOUSE OVER BUTTON>"<<std::endl;
                break;
            case SDL_MOUSEBUTTONDOWN:
                button_current_sprite = BUTTON_SPRITE_MOUSE_DOWN;
                Mix_PlayChannel(-1, button_click, 0);
                destroy_button();
                break;
            }
        }
    }
}

//buttons objects!!!!!!!!!!!!!!!!!!!

Button button_start;
SDL_Rect button_sprite_clips[BUTTON_SPRITE_TOTAL];
Button button_music_switch;
Button button_sounds_switch;


bool init_button()
{
    bool success = true;
    button_start = Button();
    
    return success;
}

bool init_button_media()
{
    bool succes = true;
    if(!button_start.button_load_media("img/start.png"))
    {
        std::cout<<"Failed to load button media!"<<std::endl;
        succes = false;
    }
    else if(!(intit_button_ttf_font()))
    {
        std::cout<<"Failed to load button ttf font!"<<std::endl;
        succes = false;
    }

 




    for(int i = 0; i < BUTTON_SPRITE_TOTAL; ++i)
    {
        button_sprite_clips[i].x = 0;
        button_sprite_clips[i].y = i * 100;
        button_sprite_clips[i].w = BUTTON_WIDTH;
        button_sprite_clips[i].h = BUTTON_HEIGHT;
    }
    

    button_start.button_set_position(355, 345);
    button_music_switch.button_set_position(10, 10);
    button_sounds_switch.button_set_position(10, 50);

    return succes;
}

void destroy_button()
{
    button_start.~Button();
}

void start()
{
    if (!init_button_media())
    {
        std::cout << "Failed to initialize!" << std::endl;
        return;
    }

    SDL_Texture *existing_texture = SDL_CreateTextureFromSurface(renderer, main_window_surface_jpg);
    if(existing_texture == NULL)
    {
        std::cout<<"Failed to create texture from surface!"<<std::endl;
        destroy_button();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(main_window);
        IMG_Quit();
        SDL_Quit();
        return;
    }

    bool quit = false;
    SDL_Event e;

    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT)
            {
                quit = true;
            }
            button_start.button_handle_event(&e);
            button_music_switch.button_handle_event(&e);
           
    
        }
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, existing_texture, NULL, NULL);
        button_start.button_render(button_start.button_get_position_x(), button_start.button_get_position_y(), &button_sprite_clips[button_start.button_current_sprite]);
        
        //button settings !!!!!!!!!!!!!!!!!!!!
        create_button_set("Music : ON", 10, 10, {0xFF, 0xFF, 0xFF});
        create_button_set("Sounds : ON", 10, 50, {0xFF, 0xFF, 0xFF});
        SDL_RenderPresent(renderer);
        
    } 
   
}
