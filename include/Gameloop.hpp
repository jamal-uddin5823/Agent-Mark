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
bool obsflag=0,lifeflag;

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



void gameloop(bool& gameRunning){


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
        else if(flag==1){
            curr_agent_frame = jumping_agent[agent_frame_no/jumping_agent.size()];
            Mix_PlayChannel(-1,jump,0);
        }
        else{
            curr_agent_frame = sliding_agent[agent_frame_no/sliding_agent.size()];
            Mix_PlayChannel(-1,slide,0);
        }
        curr_enemy_frame = running_enemy[enemy_frame_no/running_enemy.size()];
        
        music(flag);


        //rendering player
        if(flag==0|| flag==-1)
            window.render(curr_agent_frame);
        else if(flag==1)
            window.render(curr_agent_frame,1);


        //rendering obstacle
        window.renderObstacle(obstacle,obsflag);
        int coin = window.random(1,100);
        if(coin>40)
            obsflag=!obsflag;
        // window.renderObstacle(obstacleup,1);
        

        window.render(curr_enemy_frame);
        // running_enemy[enemy_frame_no/running_enemy.size()].changepos(ENEMY_VEL,0);



        agent_frame_no++;
        enemy_frame_no++;
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

        // for (int i = 0; i < (int)running_enemy.size(); i++)
        // {
        //     running_enemy[i].move(ENEMY_VEL,0);
        // }






        
        int blackBox_x=0,blackBox_y = SCREEN_HEIGHT-96;
        for (int i = 0; i < 40; i++)
        {
            Entity newgrass = Entity(Vector2f(blackBox_x,blackBox_y),blackBoxTexture,96,96,0,0);
            // int randNum = rand()%(100-1 + 1) +1;
            // if(randNum!=2 || randNum!=32)
            window.render(newgrass);
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
            // ENEMY_VEL+=0.1;
        }

        bool collideObstacle=curr_agent_frame.checkCollision(curr_agent_frame.getpos().x,curr_agent_frame.getpos().x+curr_agent_frame.getCurrentFrame().w,curr_agent_frame.getpos().y,curr_agent_frame.getpos().y+curr_agent_frame.getCurrentFrame().h,obstacle.getpos().x,obstacle.getpos().x+obstacle.getCurrentFrame().w,obstacle.getpos().y,obstacle.getpos().y+obstacle.getCurrentFrame().h,flag);
        bool collideEnemy=curr_agent_frame.checkCollision(curr_agent_frame.getpos().x,curr_agent_frame.getpos().x+curr_agent_frame.getCurrentFrame().w,curr_agent_frame.getpos().y,curr_agent_frame.getpos().y+curr_agent_frame.getCurrentFrame().h,curr_enemy_frame.getpos().x,curr_enemy_frame.getpos().x+curr_enemy_frame.getCurrentFrame().w-75,curr_enemy_frame.getpos().y,curr_enemy_frame.getpos().y+curr_enemy_frame.getCurrentFrame().h,flag);

        if(collideObstacle==true || collideEnemy==true){
            Mix_PlayChannel(-1,collision,0);
            if(collideEnemy==true){
                Mix_PlayChannel(-1,death,0);
                SDL_Delay(500);
                gameRunning=false;
                return;
            }

            obstacle.getpos().x=-100;
            // gameRunning=false;
            // std::cout<<life<<'\n';


            life--;
            if(life==0){
                Mix_PlayChannel(-1,death,0);
                SDL_Delay(500);
                gameRunning=false;
            }
            collideObstacle=false;
            for (int i = 0; i < (int)running_enemy.size(); i++)
            {
                running_enemy[i].changepos(100,0);
            }
        }
        
        window.score_show();
        window.lives_show(life);
        // window.renderlifeline(lifeline,1);
        window.display();
        SDL_Delay(1000/30);


}
