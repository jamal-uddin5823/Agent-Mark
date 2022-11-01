#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_timer.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_mixer.h>

#include<iostream>
#include<vector> 

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Events.hpp"
#include "Sprites.hpp"
#include "Gameloop.hpp"
#include "Music.hpp"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 960



int main(int argc, char *argv[])
{
    initSDL();

    bool gameRunning = true;


    SDL_Event e;
    while (gameRunning)
    {
        Handle_event(e,gameRunning);
        if(!gameRunning)
            break;

        gameloop();
        
    }
    
    
    window.cleanUp();
    
    quit();

    return 0;
}
