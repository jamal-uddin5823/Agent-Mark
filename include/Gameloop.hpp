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
                // if(game_status==NEWGAMEPLAY){
                //     one_game_time = (int)(SDL_GetTicks()/1000);
                //     init_score_life();
                // }
            }
        }
        if(game_status==GAMEOVER){
            handleMouseEvent(e,406,712,483,127,GAMEOVERBUTTON,gameRunning);
			// write_history(score,life,OBSTACLE_SPEED,running_agent[enemy_frame_no/running_agent.size()].getpos().x,running_enemy[enemy_frame_no/running_enemy.size()].getpos().x,obstacle_array[0],obstacle_array[1],lifeline);
            // highscorewrite();
            firstgameplay_loop=true;
        }
        if(game_status==HIGHSCORE){
            handleMouseEvent(e,22,22,235,90,BACKBUTTON,gameRunning);
        }
        if(game_status==OPTIONS){
            handleMouseEvent(e,694,167,163,108,MUSICBUTTON,gameRunning);
            handleMouseEvent(e,22,22,235,90,BACKBUTTON,gameRunning);
        }
        

        movement = curr_agent_frame.handleEvent(e,&agent_frame_select_flag, &paused_flag);
    }
}


void gameloop(bool& gameRunning){
    if(game_status==WELCOME_SCREEN){
        start_screen();
        
    }
    if(game_status==MAIN_MENU){
        
        if(Mix_PlayingMusic()==0 && !mute){
            Mix_PlayMusic(menuMusic,-1);
        }
        
        main_menu();
    }
    if(game_status==HIGHSCORE){
        window.render(high_score);
        highscoreshow();
    }
    if(game_status==OPTIONS){
        if(mute){
            window.render(optionsMute);
        }
        else{
            window.render(optionsUnmute);
        }
        if(mute && Mix_PlayingMusic()==1){
            Mix_HaltMusic();
        }
        if(Mix_PlayingMusic()==0 && !mute){
            Mix_PlayMusic(menuMusic,-1);
        }
    }
    if(game_status==NEWGAMEPLAY || game_status== LOADGAMEPLAY){
        // std::cout<<game_status;
        if(count>0){
            if(Mix_PlayingMusic()==1){
                Mix_HaltMusic();
            }
            countdown();
        }
        else{
            // if(game_status==LOADGAMEPLAY){
            //     init_score_life();
            // if(firstgameplay_loop){
            //     init_score_life();
            //     firstgameplay_loop=false;
            // }
            game(gameRunning);
        }
    }
    if(game_status==GAMEOVER){
        count=3;
        count_down_flag=0;

        score=0;
        life=3;
        initial_score=0;
        obstacle_array[0].setpos(1500,600);
        obstacle_array[1].setpos(2250,600);
        if(Mix_PlayingMusic()==1){
            Mix_HaltMusic();
        }
        firstgameplay_loop=true;
        window.render(game_over);
    }
    
    window.display();
    //if(paused)SDL_Delay(1000000000);
    //if(paused_flag==true)SDL_Delay=100000000;
    if((int)SDL_GetTicks()<noDamage)SDL_Delay(1000/60);
    else SDL_Delay(1000/30);

}



