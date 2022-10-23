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

std::pair<int,int> Entity::handleEvent(SDL_Event& e){
    // int agent_frame=0;
    std::pair<int,int> movement;
    if(e.type==SDL_KEYDOWN && e.key.repeat==0){
        switch (e.key.keysym.sym)
        {
        case SDLK_UP:
            vel_y-=VELOCITY;
            break;
        case SDLK_DOWN:
            vel_y+=VELOCITY;
            break;
        case SDLK_LEFT:
            vel_x-=VELOCITY;
            break;
        case SDLK_RIGHT:

            vel_x+=VELOCITY;
            break;
        }
    }
    else if(e.type==SDL_KEYUP && e.key.repeat==0){
        switch (e.key.keysym.sym)
        {
        case SDLK_UP:
            vel_y+=VELOCITY;
            break;
        case SDLK_DOWN:
            vel_y-=VELOCITY;
            break;
        // case SDLK_LEFT:
        //     vel_x+=VELOCITY;
        //     break;
        // case SDLK_RIGHT:
        //     // right_down=  false; 
        //     vel_x-=VELOCITY;
        //     // state = false;
            // break;
        }
    }
    if(pos.y!=960){
        pos.y=960-210;
        vel_y=0;
    }
        // if(pos.y>SCREEN_HEIGHT-210)
        //     vel_y-=VELOCITY;
    movement = {vel_x,vel_y};
    return movement;
    // return agent_frame;
}

void Entity::move(int x, int y){
    pos.x+=x;
    pos.y+=y;
}