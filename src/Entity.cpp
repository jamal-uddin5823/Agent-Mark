#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_timer.h>
#include<iostream>

#include "Entity.hpp"



Entity::Entity(Vector2f p_pos,SDL_Texture* p_tex, int p_w, int p_h, int p_x, int p_y)
    :pos(p_pos),tex(p_tex)
{
    current_frame.x = p_x;
    current_frame.y = p_y;
    current_frame.w=p_w;
    current_frame.h=p_h;

    vel_x = 0;
    vel_y = 0;
}


SDL_Texture* Entity::getTex(){
    return tex;
}

SDL_Rect Entity::getCurrentFrame(){
    return current_frame;
}



std::pair<int,int> Entity::handleEvent(SDL_Event& e, int* flag){
    std::pair<int,int> movement;
    if(e.type==SDL_KEYDOWN && e.key.repeat==0){
        switch (e.key.keysym.sym)
        {
        case SDLK_UP:
            // vel_y-=VELOCITY;
            *flag=1;
            break;
        case SDLK_DOWN:
            *flag=-1;
            // vel_y+=VELOCITY;
            break;
        case SDLK_LEFT:
            vel_x-=VELOCITY;
            break;
        case SDLK_RIGHT:

            vel_x+=VELOCITY;
            break;
        default:
            *flag=0;
            break;
        }
    }
    // else if(e.type==SDL_KEYUP && e.key.repeat==0){
    //     switch (e.key.keysym.sym)
    //     {
    //     case SDLK_UP:
    //         *flag=0;
    //         break;
    //     case SDLK_DOWN:
    //         *flag=0;
    //         break;
    //     // case SDLK_LEFT:
    //     //     vel_x+=VELOCITY;
    //     //     break;
    //     // case SDLK_RIGHT:
    //     //     // right_down=  false; 
    //     //     vel_x-=VELOCITY;
    //     //     // state = false;
    //     //     break;
    //     default:
    //         *flag=0;
    //         break;
    //     }
    // }
    movement = {vel_x,vel_y};
    return movement;
}

void Entity::move(int x, int y){
    pos.x+=x;
    pos.y+=y;
}