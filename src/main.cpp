#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_timer.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_mixer.h>

#include<iostream>
#include<vector> 

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Init.hpp"
#include "Sprites.hpp"
#include "Gameloop.hpp"
#include "Music.hpp"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 960



int main(int argc, char *argv[])
{
    initSDL();
    init_score_life();

    bool gameRunning = true;



    while (gameRunning)
    {
        Handle_event(gameRunning);
        if(!gameRunning)
            break;

        gameloop(gameRunning);
        
    }
    
    
    window.cleanUp();
    
    quit();

    return 0;
}
