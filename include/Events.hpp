#pragma once

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_timer.h>
#include<iostream>
#include<string>

void initSDL(){
    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER)>0){
        std::cout<<"SDL VIDEO or TIMER FAILED. "<<SDL_GetError()<<'\n';
    }

    if(!IMG_Init(IMG_INIT_PNG)){
        std::cout<<"IMG INIT FAILED. "<<SDL_GetError()<<'\n';
    }
}