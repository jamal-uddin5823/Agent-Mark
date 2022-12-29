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
#include "Mouse.hpp"

#define NEW_GAME false
#define CONTINUE_PREV_GAME true
#define first_page_change 90

enum Buttons{
	BUTTONX,
	NEW_GAMEBUTTONY,
	LOAD_GAMEBUTTONY,
	HIGHSCOREBUTTONY,
	OPTIONSBUTTONY,
	EXITBUTTONY,
	TOTAL_BUTTONS
};

int button_arr[TOTAL_BUTTONS] = {840,107,255,403,556,701};


int first_page_time = 0; //counter to count time spent on startscreen


const int VEL_X=20;
double ENEMY_VEL=0.25;
int agent_frame_no = 0,enemy_frame_no=0;
bool obsflag=0,lifeflag=0;
int agent_frame_select_flag=0;
int initial_score = 0;
bool first_loop = false;
bool life_present_prev = false;
std::pair<int,int> movement;

extern int time_passed;
int extra_time = 0;

bool gameStarted = false;

Entity curr_agent_frame = running_agent[agent_frame_no/running_agent.size()];
Entity curr_enemy_frame = running_enemy[enemy_frame_no/running_enemy.size()];


void init_score_life();
void background_scroll();
void select_agent_frame();
void render_agent();
void render_enemy();
void render_obstacle();
void update_agent_pos();
void render_ground();
void reset_frame_no();
void collision_checker(bool& gameRunning);
void render_lifeline();
int generate_score();



void init_score_life(){
    if(continue_flag==CONTINUE_PREV_GAME){
        read_history(&initial_score,&life,&OBSTACLE_SPEED,&life_present_prev);
    }
}



void background_scroll(){
    static int scrollingOffset = 0;
    scrollingOffset-=5;

    if(scrollingOffset< -background.getCurrentFrame().w)
        scrollingOffset = 0;

    window.renderBG(scrollingOffset,0,background);
    window.renderBG(scrollingOffset+background.getCurrentFrame().w,0,background);
}


void select_agent_frame(){
    if(agent_frame_select_flag==0)
            curr_agent_frame = running_agent[agent_frame_no/running_agent.size()];
    else if(agent_frame_select_flag==1){
        curr_agent_frame = jumping_agent[agent_frame_no/jumping_agent.size()];
        Mix_PlayChannel(-1,jump,0);
    }
    else{
        curr_agent_frame = sliding_agent[agent_frame_no/sliding_agent.size()];
        Mix_PlayChannel(-1,slide,0);
    }
    curr_enemy_frame = running_enemy[enemy_frame_no/running_enemy.size()];

}

void render_agent(){
    if(agent_frame_select_flag==0|| agent_frame_select_flag==-1)
            window.render(curr_agent_frame);
    else if(agent_frame_select_flag==1)
        window.render(curr_agent_frame,1);
}

void render_enemy(){
    window.render(curr_enemy_frame);
}


void render_obstacle(){
    for(int i=0;i<(int)obstacle_array.size();i++){
        if(abs(obstacle_array[0].getpos().x-obstacle_array[1].getpos().x-obstacle_array[1].getCurrentFrame().w)<100){
            obstacle_array[1].changepos(500,0);
            // obstacle_array[1].setpos(-100,600);
        }
        window.renderObstacle(obstacle_array[i],obsflag,&OBSTACLE_SPEED);
        int coin = window.random(1,100);
        if(coin>50)
            obsflag=!obsflag;
    }
}

void update_agent_pos(){
    for (int i = 0; i < (int)running_agent.size(); i++)
    {
        running_agent[i].changepos(movement.first,movement.second);
    }
    for (int i = 0; i < (int)jumping_agent.size(); i++)
    {
        jumping_agent[i].changepos(movement.first,movement.second);
    }
    for (int i = 0; i < (int)sliding_agent.size(); i++)
    {
        sliding_agent[i].changepos(movement.first,movement.second);
    }
}

void render_ground(){
    int blackBox_x=0,blackBox_y = SCREEN_HEIGHT-96;
    for (int i = 0; i < 40; i++)
    {
        Entity newgrass = Entity(Vector2f(blackBox_x,blackBox_y),blackBoxTexture,96,96,0,0);
        window.render(newgrass);
        blackBox_x+=32;
    }
}

void reset_frame_no(){
    if(agent_frame_no/running_agent.size()>=running_agent.size() && agent_frame_select_flag==0){
            agent_frame_no=0;
    }
    if(agent_frame_no/jumping_agent.size()>=jumping_agent.size() && agent_frame_select_flag==1){
        agent_frame_no=0;
        agent_frame_select_flag=0;
    }
    if(agent_frame_no/sliding_agent.size()>=sliding_agent.size() && agent_frame_select_flag==-1){
        agent_frame_no=0;
        agent_frame_select_flag=0;
    }
    if(enemy_frame_no/running_enemy.size()>=running_enemy.size()){
        enemy_frame_no=0;
        // ENEMY_VEL+=0.1;
    }
}

void collision_checker(bool& gameRunning){
    for(int i=0;i<(int)obstacle_array.size();i++){
            bool collideObstacle=curr_agent_frame.checkCollision(curr_agent_frame,obstacle_array[i],agent_frame_select_flag);
            bool collideEnemy=curr_agent_frame.checkCollision(curr_agent_frame,curr_enemy_frame,agent_frame_select_flag);
            bool collideLifeline = curr_agent_frame.checkCollision(curr_agent_frame,lifeline,agent_frame_select_flag);

            if(collideObstacle==true || collideEnemy==true){
                Mix_PlayChannel(-1,collision,0);
                if(collideEnemy==true){
                    life=0;
                    Mix_PlayChannel(-1,death,0);
                    SDL_Delay(1000);
                    gameRunning=false;
                    return;
                }
                if(collideObstacle==true)
                    obstacle_array[i].getpos().x=-100;



                life--;
                if(life<=0){
                    Mix_PlayChannel(-1,death,0);
                    SDL_Delay(1000);
                    gameRunning=false;
                }
                collideObstacle=false;

                for (int i = 0; i < (int)running_enemy.size(); i++)
                {
                    running_enemy[i].changepos(50,0);
                }
            }

            if(collideLifeline==true){
                Mix_PlayChannel(-1,lifeup,0);
                life++;
                lifeline.getpos().x=-100;
            }
        }
}


void render_lifeline(){
    int lifecoin = window.random(1,1000);
    if(lifecoin>995){
        lifeflag=1;
    }
    if(lifeflag||life_present_prev){
        window.render(lifeline);
        lifeline.changepos(-5,0);
        if(lifeline.getpos().x+lifeline.getCurrentFrame().w<0){
            lifeline.setpos(SCREEN_WIDTH,SCREEN_HEIGHT-200);
            lifeflag=false;
        }
        life_present_prev=false;
    }
}


int generate_score(){
    int time = (int)(SDL_GetTicks()/1000);
    time-=extra_time+5;
    time_passed= time;
    if(time_passed%10==0 && time_passed!=0){
        Mix_PlayChannel(-1,levelup,0);
    }
    window.score_show(time,initial_score);
    return initial_score+ time;
}


