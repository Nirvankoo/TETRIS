#ifndef BUTTON_H
#define BUTTON_H
#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include"window.h"
#include"game.h"

enum Button_current_sprite
{
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 2,
    BUTTON_SPRITE_MOUSE_UP = 3,
    BUTTON_SPRITE_TOTAL = 4
};

class Button
{
    public:
    Button();
    ~Button();
    Button(std::string name, int widht, int height);
    std::string button_name;

    bool button_load_media(std::string path);
    void button_render(int x, int y, SDL_Rect* clip = NULL);
    int button_get_width();
    int button_get_height();
    void button_set_position(int x, int y);
    int button_get_position_x();
    int button_get_position_y();
    void button_handle_event(SDL_Event* e);
    Button_current_sprite button_current_sprite;
   

    private:
    SDL_Texture *button_texture;
    int width;
    int height;
    SDL_Point button_position;
   
};

bool init_button_media();
void destroy_button();
void start();





    




#endif