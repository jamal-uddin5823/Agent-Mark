#pragma once

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_timer.h>
#include<iostream>
#include<string>


#include "Sprites.hpp"

const int VEL_X=20;
double ENEMY_VEL=0.25;


int agent_frame = 0,enemy_frame=0;

Entity curr_agent_frame = running_agent[agent_frame/running_agent.size()];
Entity curr_enemy_frame = running_enemy[enemy_frame/running_enemy.size()];
std::pair<int,int> movement;

void Handle_event(SDL_Event& e, bool& gameRunning){
    while (SDL_PollEvent(&e))
    {
        if(e.type == SDL_QUIT){
            gameRunning=false;
        }
        movement = curr_agent_frame.handleEvent(e);
    }
}



void gameloop(){
        window.clearScreen();
        window.changeRenderColor(255,255,255,255);
        window.render(background,2);

        int blackBox_x=0,blackBox_y = SCREEN_HEIGHT/3-32;
        
        curr_agent_frame = running_agent[agent_frame/running_agent.size()];
        curr_enemy_frame = running_enemy[enemy_frame/running_enemy.size()];

        
        window.render(curr_agent_frame,1);
        window.render(curr_enemy_frame,1);
        running_enemy[enemy_frame/running_enemy.size()].changepos(0.25,0);



        agent_frame++;
        enemy_frame++;
        for (int i = 0; i < (int)running_agent.size(); i++)
        {
            running_agent[i].move(movement.first,movement.second);
        }
        
        for (int i = 0; i < 40; i++)
        {
            Entity newgrass = Entity(Vector2f(blackBox_x,blackBox_y),blackBoxTexture,32,32,0,0);
            // int randNum = rand()%(100-1 + 1) +1;
            // if(randNum!=2 || randNum!=32)
            window.render(newgrass,3);
            blackBox_x+=32;
            // SDL_Delay(1000/900);
        }

        if(agent_frame/running_agent.size()>=running_agent.size()){
            agent_frame=0;
        }
        if(enemy_frame/running_enemy.size()>=running_enemy.size()){
            enemy_frame=0;
            ENEMY_VEL+=0.2;
        }
        
        window.display();
        SDL_Delay(1000/30);

}
