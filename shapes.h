#ifndef SHAPES_H
#define SHAPES_H
#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<string>

class Shape
{
public:
Shape();
Shape(std::string name, SDL_Color color, int shapeType[4][4], int x, int y);
virtual ~Shape();


void render_shape(int x, int y, SDL_Rect* clip = NULL);
bool load_shape_media(std::string path);
void handle_shape_event(SDL_Event* e);

void set_shape_name(std::string name);
void set_shape_color(SDL_Color color);
void set_shape_type(int shapeType[4][4]);
void set_shape_position_x(int x){
    this->x += x;
};
void set_shape_position_y(int y){
    this->y += y;
};
std::string get_shape_name();
SDL_Color get_shape_color();
int get_shape_x();
int get_shape_y();
void set_shape_width(int width);
void set_shape_height(int height);
int get_shape_width();
int get_shape_height();

protected:
SDL_Texture* shape_texture;
std::string name;
SDL_Color color;
int shapeType[4][4];
int x, y; // position of the shape
int width;
int height;

};


class Square : protected Shape
{
public:
Square() : Shape(){}
~Square(){}
Square(std::string name, SDL_Color color, int shapeType[4][4], int x, int y) : Shape(name, color, shapeType, x, y){}

};

class Line : protected Shape
{
public:
Line() : Shape(){}
~Line(){}
Line(std::string name, SDL_Color color, int shapeType[4][4], int x, int y) : Shape(name, color, shapeType, x, y){}

};

class Z :protected Shape
{
public:
Z() : Shape(){}
~Z(){}
Z(std::string name, SDL_Color color, int shapeType[4][4], int x, int y) : Shape(name, color, shapeType, x, y){}

};

class S : protected Shape
{
public:
S() : Shape(){}
~S(){}
S(std::string name, SDL_Color color, int shapeType[4][4], int x, int y) : Shape(name, color, shapeType, x, y){}

};


class L : protected Shape
{
public:
L() : Shape(){}
~L(){}
L(std::string name, SDL_Color color, int shapeType[4][4], int x, int y) : Shape(name, color, shapeType, x, y){}


};

class J : protected Shape
{
public:
J() : Shape(){}
~J(){}
J(std::string name, SDL_Color color, int shapeType[4][4], int x, int y) : Shape(name, color, shapeType, x, y){}
};

class T : protected Shape
{
public:
T() : Shape(){}
~T(){}
T(std::string name, SDL_Color color, int shapeType[4][4], int x, int y) : Shape(name, color, shapeType, x, y){}

};

#endif // SHAPES_H

void create_shapes(Shape obj);


