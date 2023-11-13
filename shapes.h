#ifndef SHAPES_H
#define SHAPES_H
#include<SDL2/SDL.h>
#include<string>




//base class of all shapes
class Shape
{
    private:
    SDL_Texture *shape_texture;
    std::string name;
    SDL_Color shape_color;
    int cord_x;
    int cord_y;
    int shape_width;
    int shape_height;
    int shape_type[4][4];



    
    public:
    Shape();
    Shape(std::string name, int cord_x, int cord_y);
    virtual ~Shape();

    void render_shape(int x, int y, SDL_Rect *clip = NULL);
    bool load_shape_media(std::string path);
    void handle_shape_event(SDL_Event *e);

    //setters
    
    void set_shape_name(std::string name);
    void set_shape_color(SDL_Color shape_color);
    void set_shape_type(int shape_type[4][4]);
    void set_shape_cord_x(int cord_x);
    void set_shape_cord_y(int cord_y);
    void set_shape_width(int shape_width);
    void set_shape_height(int shape_height);


    //getters
    std::string get_shape_name();
    SDL_Color get_shape_color();
    int get_shape_type(int i, int j);
    int get_shape_cord_x();
    int get_shape_cord_y();
    int get_shape_width();
    int get_shape_height();

    //miscilaneous

    bool inside_grid(int offset);
    static Shape *create_shapes(const std::string &name);
};

class Square : public Shape
{
     public:
     Square() : Shape(){
     int square_type[4][4] = {
            {1, 1, 0, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}};

        set_shape_type(square_type);
        set_shape_name("Square");
        set_shape_cord_x(460);
        set_shape_cord_y(0);
        set_shape_width(40);
        set_shape_height(40);
     }
    
   
    
};

class Line : public Shape
{
    public:
    Line() : Shape(){
    int square_type[4][4] = {
            {1,1, 0, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}};

        set_shape_type(square_type);
        set_shape_name("line");
        set_shape_cord_x(460);
        set_shape_cord_y(0);
        set_shape_width(40);
        set_shape_height(40);
     }
    

};

class T : public Shape
{
    public:
    T() : Shape()
    {
        int l_shape_type[4][4] = {
            {1, 1, 1, 0},
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 0, 0}};

        set_shape_type(l_shape_type);
        set_shape_name("T");
        set_shape_cord_x(460);
        set_shape_cord_y(0);
        set_shape_width(40);
        set_shape_height(40);
    
    }   
};

class L : public Shape
{
    public:
    L() : Shape()
    {
        int t_shape_type[4][4] = {
            {1, 0, 0, 0},
            {1, 0, 0, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0}};

        set_shape_type(t_shape_type);
        set_shape_name("L");
        set_shape_cord_x(460);
        set_shape_cord_y(0);
        set_shape_width(40);
        set_shape_height(40);
    };
   
};

class Lm : public Shape
{
    public:
    Lm() : Shape()
    {
        int z_shape_type[4][4] = {
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0}};

        set_shape_type(z_shape_type);
        set_shape_name("Lm");
        set_shape_cord_x(460);
        set_shape_cord_y(0);
        set_shape_width(40);
        set_shape_height(40);
    };
    ~Lm(){};

    

};

class Z : public Shape
{
    public:
    Z() : Shape()
    {
        int s_shape_type[4][4] = {
            {1, 1, 0, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}};

        set_shape_type(s_shape_type);
        set_shape_name("Z");
        set_shape_cord_x(460);
        set_shape_cord_y(0);
        set_shape_width(40);
        set_shape_height(40);
    };
    
    ~Z(){};
   

};

class Zm : public Shape
{
    public:
    Zm() : Shape()
    {
        int j_shape_type[4][4] = {
            {0, 1, 1, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}};

        set_shape_type(j_shape_type);
        set_shape_name("Zm");
        set_shape_cord_x(460);
        set_shape_cord_y(0);
        set_shape_width(40);
        set_shape_height(40);
    };
    
    ~Zm(){};
    

};

extern Shape *current_shape;
extern bool next_shape_flag;

Shape create_shapes(const std::string &name);

    

#endif