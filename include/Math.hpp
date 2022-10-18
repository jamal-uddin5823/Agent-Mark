#pragma once

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_timer.h>
#include<iostream>
#include<string>



struct Vector2f
{
    Vector2f()
        :x(0.0f),y(0.0f)
    {}

    
    Vector2f(float p_x,float p_y)
        :x(p_x),y(p_y)
    {}

    void print(){
        std::cout<<x<<","<<y<<'\n';
    }

    
    float x, y;
};
