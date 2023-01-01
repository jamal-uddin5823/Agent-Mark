#pragma once

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_timer.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_mixer.h>

#include<iostream>
#include<string>

// #include "Mouse.hpp"

Mix_Music *gMusic = NULL;
Mix_Music *menuMusic = NULL;
Mix_Chunk* jump = NULL;
Mix_Chunk* slide = NULL;
Mix_Chunk* collision = NULL;
Mix_Chunk* death = NULL;
Mix_Chunk* lifeup = NULL;
Mix_Chunk* levelup = NULL;


bool loadMedia()
{
    //Loading success flag
    bool success = true;

    //Load prompt texture

    //Load start music
    menuMusic = Mix_LoadMUS("sounds/theme.wav");
    if( menuMusic == NULL )
    {
        printf( "Failed to load start music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    //Load music
    gMusic = Mix_LoadMUS( "sounds/chase.mp3" );
    if( gMusic == NULL )
    {
        printf( "Failed to load theme music! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    //Load sound effects
    jump = Mix_LoadWAV( "sounds/jump.wav" );
    if( jump == NULL )
    {
        printf( "Failed to load jump sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    slide = Mix_LoadWAV( "sounds/slide.wav" );
    if( slide == NULL )
    {
        printf( "Failed to load slide sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    collision = Mix_LoadWAV("sounds/Collision.mp3");
    if( collision == NULL )
    {
        printf( "Failed to load collision sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    death = Mix_LoadWAV("sounds/death.mp3");
    if( death == NULL )
    {
        printf( "Failed to load death sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    lifeup = Mix_LoadWAV("sounds/lifeup.mp3");
    if( lifeup == NULL )
    {
        printf( "Failed to load lifeup sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    levelup = Mix_LoadWAV("sounds/levelup.mp3");
    if( levelup == NULL )
    {
        printf( "Failed to load levelup sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
    
    return success;
}

void music(int flag){
    //The music that will be played

    // Mix_PlayMusic( gMusic, -1 );
    // SDL_Delay(1000);
    // bool play = true;
    if( Mix_PlayingMusic() == 0 )
    {
        //Play the music
        switch (flag)
        {
        case 0:
            if(Mix_PlayingMusic()==0){
                Mix_PlayMusic(gMusic,-1);
            }
            else
            {
                //If the music is paused
                if( Mix_PausedMusic() == 1 )
                {
                    //Resume the music
                    Mix_ResumeMusic();
                }
                //If the music is playing
                else
                {
                    //Pause the music
                    Mix_PauseMusic();
                }
            }
            break;
        
        
        default:
            break;
        }
    }

}
