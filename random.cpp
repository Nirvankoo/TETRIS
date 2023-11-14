#include <iostream>
#include <SDL2/SDL.h>
#include <cstdlib>
#include <ctime>
#include <string>
#include"random.h"

std::string pick_rand_shape()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::string shape_array[7] = {"Square", "Line", "T", "L", "Lm", "Z", "Zm"};
    int array_size = sizeof(shape_array) / sizeof(shape_array[0]);
    int random_index = std::rand() % array_size;
    return shape_array[random_index];
}