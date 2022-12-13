#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_timer.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_mixer.h>

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

    movement = {vel_x,vel_y};
    return movement;
}

bool Entity::checkCollision(Entity player, Entity collider, int slide)
{
    int leftA = player.getpos().x;
    int rightA = player.getpos().x+player.getCurrentFrame().w;
    int topA = player.getpos().y;
    int bottomA = player.getpos().y+player.getCurrentFrame().h;

    int leftB = collider.getpos().x;
    int rightB = collider.getpos().x+collider.getCurrentFrame().w;
    int topB = collider.getpos().y;
    int bottomB = collider.getpos().y+collider.getCurrentFrame().h;


    if(slide==-1){
        topA+=10;
    }

    //If any of the sides from A are outside of B
    if( bottomA < topB )
    {
        return false;
    }
 
    if( topA > bottomB )
    {
        return false;
    }
 
    if( rightA < leftB )
    {
        return false;
    }
 
    if( leftA > rightB )
    {
        return false;
    }
 
    //If none of the sides from A are outside B
    return true;
}



