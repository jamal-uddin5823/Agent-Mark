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
#include "Fileio.hpp"


#define NEW_GAME false
#define CONTINUE_PREV_GAME true
#define first_page_change 90


enum{
    START_SCREEN,
    MAIN_MENU,
};

int game_status = START_SCREEN;
int first_page_time = 0;


