#pragma once

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_timer.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_mixer.h>

#include<iostream>
#include<string>

#include "Sprites.hpp"
#include "Music.hpp"



void initSDL(){
    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_AUDIO)>0){
        std::cout<<"SDL VIDEO or TIMER or AUDIO FAILED. "<<SDL_GetError()<<'\n';
    }

    if(!IMG_Init(IMG_INIT_PNG)){
        std::cout<<"IMG INIT FAILED. "<<SDL_GetError()<<'\n';
    }
    if( TTF_Init() == -1 )
    {
        std::cout<< "SDL_ttf could not initialize! SDL_ttf Error: "<< TTF_GetError() <<'\n';
    }
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        std::cout<<"SDL_mixer could not initialize! SDL_mixer Error: "<<Mix_GetError()<<'\n';
    }

    loadMedia();
}


void quit(){
    IMG_Quit();
    
    SDL_StopTextInput();
    // TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
    
}