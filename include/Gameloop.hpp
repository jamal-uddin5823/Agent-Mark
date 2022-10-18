#pragma once

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_timer.h>
#include<iostream>
#include<string>


#include "Sprites.hpp"

const int VEL_X=20;


int frame = 0;

Entity current_frame = running_boy[frame/running_boy.size()];
std::pair<int,int> movement;

void Handle_event(SDL_Event& e, bool& gameRunning){
    while (SDL_PollEvent(&e))
    {
        if(e.type == SDL_QUIT){
            gameRunning=false;
        }
        movement = current_frame.handleEvent(e);
    }
}



void gameloop(){
        window.clearScreen();
        window.changeRenderColor(255,255,255,255);

        int blackBox_x=0,blackBox_y = SCREEN_HEIGHT/3-32;
        
        current_frame = running_boy[frame/running_boy.size()];

        
        window.render(current_frame,1);

        frame++;
        for (int i = 0; i < running_boy.size(); i++)
        {
            running_boy[i].move(movement.first,movement.second);
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

        if(frame/running_boy.size()>=running_boy.size()){
            frame=0;
        }
        
        window.display();
        SDL_Delay(1000/30);

}
