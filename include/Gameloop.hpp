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

const int VEL_X=20;
double ENEMY_VEL=0.25;


int agent_frame_no = 0,enemy_frame_no=0;
bool obsflag=0,lifeflag=0;
extern int time_passed;


Entity curr_agent_frame = running_agent[agent_frame_no/running_agent.size()];
Entity curr_enemy_frame = running_enemy[enemy_frame_no/running_enemy.size()];
std::pair<int,int> movement;
int agent_frame_select_flag=0;



void Handle_event(SDL_Event& e, bool& gameRunning){
    while (SDL_PollEvent(&e))
    {
        if(e.type == SDL_QUIT){
            gameRunning=false;
        }
        movement = curr_agent_frame.handleEvent(e,&agent_frame_select_flag);
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


void render_obstacle(){
    for(int i=0;i<(int)obstacle_array.size();i++){
        if(abs(obstacle_array[0].getpos().x-obstacle_array[1].getpos().x-obstacle_array[1].getCurrentFrame().w)<100){
            obstacle_array[1].changepos(500,0);
            // obstacle_array[1].setpos(-100,600);
        }
        window.renderObstacle(obstacle_array[i],obsflag);
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
                    Mix_PlayChannel(-1,death,0);
                    SDL_Delay(1000);
                    gameRunning=false;
                    return;
                }
                if(collideObstacle==true)
                    obstacle_array[i].getpos().x=-100;



                life--;
                if(life==0){
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
    if(lifecoin>999){
        lifeflag=1;
    }
    if(lifeflag){
        window.render(lifeline);
        lifeline.changepos(-5,0);
        if(lifeline.getpos().x+lifeline.getCurrentFrame().w<0){
            lifeline.setpos(SCREEN_WIDTH,SCREEN_HEIGHT-200);
            lifeflag=0;
        }
    }
}
void generate_score(){
    int time = (int)(SDL_GetTicks()/1000);
    time_passed= time;
    if(time_passed%10==0 && time_passed!=0){
        Mix_PlayChannel(-1,levelup,0);
    }
    std::string s="Score : "+std::__cxx11::to_string(time);
    int text_w,text_h;
    SDL_Texture* texture = window.Textload(s,"fonts/Antonio-Bold.ttf",50,0,0,0,&text_w,&text_h);
    Entity score = Entity(Vector2f(10,50),texture,text_w,text_h,0,0);

    window.render(score);
}

void gameloop(bool& gameRunning){
    

    window.clearScreen();
    window.changeRenderColor(255,255,255,255);
    
    background_scroll();


    select_agent_frame();

    music(agent_frame_select_flag);


    render_agent();

    render_obstacle();
    render_lifeline();

    window.render(curr_enemy_frame);

    agent_frame_no++;
    enemy_frame_no++;

    update_agent_pos();

    render_ground();
    
    render_lifeline();

    reset_frame_no();

    collision_checker(gameRunning);

    generate_score();
    // window.score_show();
    window.lives_show(life);

    window.display();
    SDL_Delay(1000/30);

}
