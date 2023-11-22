#ifndef WINDOW_H
#define WINDOW_H
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>
#include<SDL2/SDL_ttf.h>


class Window_class{
    private:
    int height;
    int width;
    public:
    Window_class();
    ~Window_class();
    Window_class(int x, int y);
    int get_window_height();
    int get_window_width();
};

SDL_Surface *window_load_surface(const std::string &path);
bool init_window(Window_class window_class);
bool load_audio();
void close_window();



extern SDL_Window *main_window;
extern SDL_Renderer *renderer;
extern SDL_Surface *main_window_surface;
extern SDL_Surface *main_window_surface_jpg;

extern Mix_Music *music;
extern Mix_Chunk *button_click;
extern Mix_Chunk *button_hover;

extern TTF_Font *but_set_font;
extern SDL_Color but_set_color;

extern bool sound_effect;

#endif