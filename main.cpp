#include<iostream>
#include<windows.h>
#include"window.h"
#include"game.h"
#include"button.h"
#include"run.h"

int main(int argc, char* argv[])
{

    
   // HWND hwnd = GetConsoleWindow();
    //ShowWindow(hwnd, SW_HIDE);

    Window_class ob(800, 1000);
    create_game(ob);




    run();

    



    

    return 0;
}