#pragma once

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_timer.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_mixer.h>

#include<iostream>
#include<string>

#include "Entity.hpp"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 960
#define JUMPOBSTACLEY 768
#define SLIDEOBSTACLEY 600

static int OBSTACLE_POSX= 1500;

static int life=5;



struct RenderWindow{

    public:
        RenderWindow(std::string p_title, int p_w, int p_h);

        SDL_Texture* loadTexture(std::string p_filepath, bool flag,Uint8 r, Uint8 g,Uint8 b);
        SDL_Texture* Textload(std::string textureText,std::string fontpath,int fontsize, Uint8 r, Uint8 g, Uint8 b, int* w, int* h);
        void cleanUp();

        void changeRenderColor(int r,int g, int b, int a);
        void clearScreen();

        void render(Entity &p_entity, bool jump=0);
        void renderBG( int x, int y,Entity background, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
        void renderlifeline(Entity &lifeline,bool lifeflag);
        int random(int low, int high);
        void renderObstacle(Entity &obstacle, bool flagup);

        void display();
        void score_show();
        void lives_show(int& life);
        
    private:
        SDL_Window* window=NULL;
        SDL_Renderer* renderer=NULL;
};


// {
//     std::string s="Time : "+std::__cxx11::to_string((int)(SDL_GetTicks()/1000));
    
//     Textload()
// }
