#include<iostream>
#include<windows.h>
#include"window.h"
#include"game.h"
#include"button.h"
#include"shapes.h"
int main(int argc, char* argv[])
{

    
   // HWND hwnd = GetConsoleWindow();
    //ShowWindow(hwnd, SW_HIDE);

    Window_class ob(800, 1000);
    create_game(ob);




    start();

    int squareShape[4][4] = {
    {1, 1, 0, 0},
    {1, 1, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};

Shape square("square", {0, 0, 0}, squareShape, 300, 0);



    create_shapes(square);


    

    return 0;
}