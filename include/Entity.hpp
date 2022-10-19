#pragma once

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_timer.h>
#include<iostream>
#include<string>
#include<utility>

#include "Math.hpp"

static const int VELOCITY=5;

struct Entity
{
    public:
        Entity(Vector2f p_pos,SDL_Texture* p_tex, int p_w, int p_h, int p_x, int p_y);
                //pos in dest                                       //pos in source
        Vector2f& getpos(){
            return pos;
        }
        void changepos(int x, int y){
            pos.x+=x;
            pos.y+=y;
        }
        SDL_Texture* getTex();
        SDL_Rect getCurrentFrame();
        std::pair<int,int> handleEvent(SDL_Event& e);
        void move(int x, int y);

    private:
        Vector2f pos;
        SDL_Rect curr_agent_frame;
        SDL_Texture* tex;

        int vel_x,vel_y;
};
