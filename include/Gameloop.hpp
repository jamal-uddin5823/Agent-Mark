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
#include "GameStatus.hpp"
#include "Gamefuncs.hpp"



void Handle_event(bool& gameRunning){
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if(e.type == SDL_QUIT){
            gameRunning=false;
            write_history(score,life,OBSTACLE_SPEED,running_agent[enemy_frame_no/running_agent.size()].getpos().x,running_enemy[enemy_frame_no/running_enemy.size()].getpos().x,obstacle_array[0],obstacle_array[1],lifeline);
        }
        for (int button = 1; button < TOTAL_BUTTONS; button++)
        {
            if(game_status==MAIN_MENU){
                handleMouseEvent(e,button_arr[BUTTONX],button_arr[button],BUTTON_WIDTH,BUTTON_HEIGHT, button, gameRunning);
                if(game_status==GAMEPLAY){
                    init_score_life();
                }
            }
        }
        if(game_status==GAMEOVER){
            handleMouseEvent(e,712,406,127,483,GAMEOVERBUTTON,gameRunning);
        }
        

        movement = curr_agent_frame.handleEvent(e,&agent_frame_select_flag, &paused_flag);
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
    if(game_status==GAMEPLAY){
        if(count>0){
            if(Mix_PlayingMusic()==1){
                Mix_HaltMusic();
            }
            countdown();
        }
        else{
            game(gameRunning);
        }
    }
    if(game_status==GAMEOVER){
        if(Mix_PlayingMusic()==1){
            Mix_HaltMusic();
        }
        window.render(game_over);
    }
    
    window.display();
    //if(paused)SDL_Delay(1000000000);
    //if(paused_flag==true)SDL_Delay=100000000;
    if((int)SDL_GetTicks()<noDamage)SDL_Delay(1000/60);
    else SDL_Delay(1000/30);

}



