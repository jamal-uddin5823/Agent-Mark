#pragma once

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_timer.h>
#include<iostream>
#include<string>


#include "Sprites.hpp"

const int VEL_X=20;
double ENEMY_VEL=0.25;


int agent_frame_no = 0,enemy_frame_no=0;

Entity curr_agent_frame = running_agent[agent_frame_no/running_agent.size()];
Entity curr_enemy_frame = running_enemy[enemy_frame_no/running_enemy.size()];
std::pair<int,int> movement;
int flag=0;

void Handle_event(SDL_Event& e, bool& gameRunning){
    while (SDL_PollEvent(&e))
    {
        if(e.type == SDL_QUIT){
            gameRunning=false;
        }
        movement = curr_agent_frame.handleEvent(e,&flag);
    }
}



void gameloop(){
        window.clearScreen();
        window.changeRenderColor(255,255,255,255);
        // window.render(background,1);

        static int scrollingOffset = 0;
        scrollingOffset-=5;

        if(scrollingOffset< -background.getCurrentFrame().w)
            scrollingOffset = 0;

        window.renderBG(scrollingOffset,0,background);
        window.renderBG(scrollingOffset+background.getCurrentFrame().w,0,background);





        if(flag==0)
            curr_agent_frame = running_agent[agent_frame_no/running_agent.size()];
        else if(flag==1)
            curr_agent_frame = jumping_agent[agent_frame_no/jumping_agent.size()];
        else
            curr_agent_frame = sliding_agent[agent_frame_no/sliding_agent.size()];
            
        curr_enemy_frame = running_enemy[enemy_frame_no/running_enemy.size()];
        



        if(flag==0|| flag==-1)
            window.render(curr_agent_frame,1);
        else if(flag==1)
            window.renderjump(curr_agent_frame,3);
        window.render(curr_enemy_frame,1);
        running_enemy[enemy_frame_no/running_enemy.size()].changepos(0.25,0);



        agent_frame_no++;
        enemy_frame_no++;
        for (int i = 0; i < (int)running_agent.size(); i++)
        {
            running_agent[i].move(movement.first,movement.second);
        }
        for (int i = 0; i < (int)jumping_agent.size(); i++)
        {
            jumping_agent[i].move(movement.first,movement.second);
        }
        for (int i = 0; i < (int)sliding_agent.size(); i++)
        {
            sliding_agent[i].move(movement.first,movement.second);
        }



        
        int blackBox_x=0,blackBox_y = SCREEN_HEIGHT/3-32;
        for (int i = 0; i < 40; i++)
        {
            Entity newgrass = Entity(Vector2f(blackBox_x,blackBox_y),blackBoxTexture,32,32,0,0);
            // int randNum = rand()%(100-1 + 1) +1;
            // if(randNum!=2 || randNum!=32)
            window.render(newgrass,3);
            blackBox_x+=32;
        }



        if(agent_frame_no/running_agent.size()>=running_agent.size() && flag==0){
            agent_frame_no=0;
        }
        if(agent_frame_no/jumping_agent.size()>=jumping_agent.size() && flag==1){
            agent_frame_no=0;
            flag=0;
        }
        if(agent_frame_no/sliding_agent.size()>=sliding_agent.size() && flag==-1){
            agent_frame_no=0;
            flag=0;
        }
        if(enemy_frame_no/running_enemy.size()>=running_enemy.size()){
            enemy_frame_no=0;
            ENEMY_VEL+=0.2;
        }
        // flag=-1;
        window.display();
        SDL_Delay(1000/30);

}
