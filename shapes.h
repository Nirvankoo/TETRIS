#ifndef SHAPES_H
#define SHAPES_H
#include<SDL2/SDL.h>
#include<string>


//base class of all shapes
class Shape
{
    protected:
    SDL_Texture *shape_texture;
    std::string name;
    SDL_Color shape_color;
    int shape_type[4][4];
    int cord_x;
    int cord_y;
    int shape_width;
    int shape_height;



    
    public:
    Shape();
    Shape(std::string name, int shape_type[4][4], int cord_x, int cord_y);
    virtual ~Shape();

    void render_shape(int cord_x, int cord_y, SDL_Rect *clip = NULL);
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
};

class Square : protected Shape
{
    public:
    Square() : Shape(){};
    ~Square(){};
    Square(std::string name, int shape_type[4][4], int cord_x, int cord_y) : Shape(name, shape_type, cord_x, cord_y){};

};

class Line : protected Shape
{
    public:
    Line() : Shape(){};
    ~Line(){};
    Line(std::string name, int shape_type[4][4], int cord_x, int cord_y) : Shape(name, shape_type, cord_x, cord_y){};
};

class L_shape : protected Shape
{
    public:
    L_shape() : Shape(){};
    ~L_shape(){};
    L_shape(std::string name, int shape_type[4][4], int cord_x, int cord_y) : Shape(name, shape_type, cord_x, cord_y){};
};

class T_shape : protected Shape
{
    public:
    T_shape() : Shape(){};
    ~T_shape(){};
    T_shape(std::string name, int shape_type[4][4], int cord_x, int cord_y) : Shape(name, shape_type, cord_x, cord_y){};
};

class Z_shape : protected Shape
{
    public:
    Z_shape() : Shape(){};
    ~Z_shape(){};
    Z_shape(std::string name, int shape_type[4][4], int cord_x, int cord_y) : Shape(name, shape_type, cord_x, cord_y){};
};

class S_shape : protected Shape
{
    public:
    S_shape() : Shape(){};
    ~S_shape(){};
    S_shape(std::string name, int shape_type[4][4], int cord_x, int cord_y) : Shape(name, shape_type, cord_x, cord_y){};
};

class J_shape : protected Shape
{
    public:
    J_shape() : Shape(){};
    ~J_shape(){};
    J_shape(std::string name, int shape_type[4][4], int cord_x, int cord_y) : Shape(name, shape_type, cord_x, cord_y){};
};

void create_shapes(Shape obj);

    

#endif