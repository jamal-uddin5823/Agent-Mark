#pragma once

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_timer.h>
#include<iostream>
#include<string>


#include "Sprites.hpp"

const int VEL_X=20;


int frame = 0;
bool right_down = false;
Entity current_frame = running_boy[3];

void Handle_event(SDL_Event& e, bool& gameRunning){
    while (SDL_PollEvent(&e))
    {
        if(e.type == SDL_QUIT){
            gameRunning=false;
        }
        current_frame.handleEvent(e);
        // else if(e.type == SDL_KEYDOWN){
        //     switch (e.key.keysym.scancode)
        //     {
        //         case SDL_SCANCODE_RIGHT:
        //             frame++;
        //             right_down= true;
        //             running_boy[(frame)/running_boy.size()].changepos(5,0);
                    
        //             break;

            
                
        //         default:
        //             break;
        //     }
        // }
        // if(e.type == SDL_KEYUP){
        //     if(e.key.keysym.scancode==SDL_SCANCODE_RIGHT){
        //         right_down = false;
        //     }
        // }
    }
}



void gameloop(){
        window.clearScreen();
        window.changeRenderColor(255,255,255,255);

        int blackBox_x=0,blackBox_y = SCREEN_HEIGHT/3-32;
        current_frame.move();
        
        // if(!right_down)
        //     window.render(standing_boy,1);
        // else{ 
            window.render(current_frame,1);
        // }
        
        // boy[frame/boy.size()].changepos(2,0);
        // right_down= false;

        for (int i = 0; i < 40; i++)
        {
            Entity newgrass = Entity(Vector2f(blackBox_x,blackBox_y),blackBoxTexture,32,32,0,0);
            window.render(newgrass,3);
            blackBox_x+=32;
        }

        
        window.display();

        // frame++;
        // if(frame/running_boy.size()>=running_boy.size()){       
        //     frame=0;
        //     if(right_down){
        //         standing_boy.changepos(5,0);
        //         // right_down = false;
        //     }
        // }

        SDL_Delay(1000/60);

}
