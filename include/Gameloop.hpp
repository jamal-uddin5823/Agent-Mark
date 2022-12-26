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
#include "GameStages.hpp"



void Handle_event(bool& gameRunning){
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if(e.type == SDL_QUIT){
            gameRunning=false;
            write_history(score,life,OBSTACLE_SPEED,running_agent[enemy_frame_no/running_agent.size()].getpos().x,running_enemy[enemy_frame_no/running_enemy.size()].getpos().x,obstacle_array[0],obstacle_array[1],lifeline);
        }
        movement = curr_agent_frame.handleEvent(e,&agent_frame_select_flag);
    }
}


void gameloop(bool& gameRunning){
    if(game_status==WELCOME_SCREEN){
        start_screen();
        
    }
    if(game_status==MAIN_MENU){
        if(Mix_PlayingMusic()==0){
            Mix_PlayMusic(menuMusic,-1);
        }
        main_menu();
    }
    if(game_status==2){
        if(count>0){
            if(Mix_PlayingMusic()==1){
                Mix_HaltMusic();
            }
            countdown();
        }
        else
            game(gameRunning);
    }
    
    window.display();
    SDL_Delay(1000/30);

}



