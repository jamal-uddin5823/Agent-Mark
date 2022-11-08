#pragma once

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_timer.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_mixer.h>

#include<iostream>
#include<string>
#include<vector>

#include "RenderWindow.hpp"
#include "Entity.hpp"

RenderWindow window("Agent Mark", SCREEN_WIDTH,SCREEN_HEIGHT);

int blackBox_x=0,blackBox_y = SCREEN_HEIGHT/3-32;
SDL_Texture* blackBoxTexture = window.loadTexture("res/Blackbox.png",0,0,0,0); 
SDL_Texture* backTexture = window.loadTexture("res/skyline.png",1,255,255,255);
SDL_Texture* agentTexture = window.loadTexture("res/sheet.png",1,255,255,255);
SDL_Texture* enemyTexture = window.loadTexture("res/enemysheet.png",0,255,0,0);
SDL_Texture* obstacleTexture = window.loadTexture("res/Blackbox.png",0,0,0,0);


int text_w,text_h;

// SDL_Texture* scoreTexture = window.Textload("Score: "+scoregen(),"fonts/Antonio-Bold.ttf",50,0,0,255,&text_w,&text_h);






Entity standing_boy = Entity(Vector2f(100,SCREEN_HEIGHT-210),agentTexture,125,125,0,0);
// Entity newgrass = Entity(Vector2f(blackBox_x,blackBox_y),blackBoxTexture,32,32,0,0);
Entity newgrass = Entity(Vector2f(blackBox_x,blackBox_y),blackBoxTexture,32,32,0,0);



std::vector<Entity> running_agent ={
    Entity(Vector2f(200,SCREEN_HEIGHT-210),agentTexture,129,129,387,129),
    Entity(Vector2f(205,SCREEN_HEIGHT-210),agentTexture,129,129,516,129),
    Entity(Vector2f(210,SCREEN_HEIGHT-210),agentTexture,129,129,645,129),
    Entity(Vector2f(215,SCREEN_HEIGHT-210),agentTexture,129,129,774,129)
};


std::vector<Entity> jumping_agent ={
    Entity(Vector2f(200,SCREEN_HEIGHT-210),agentTexture,129,129,129*2,129*3),
    Entity(Vector2f(200,SCREEN_HEIGHT-210),agentTexture,129,129,129*3,129*3),
    Entity(Vector2f(200,SCREEN_HEIGHT-210),agentTexture,129,129,129*4,129*3),
    Entity(Vector2f(200,SCREEN_HEIGHT-210),agentTexture,129,129,129*5,129*3)
    
};
std::vector<Entity> sliding_agent ={
    Entity(Vector2f(200,SCREEN_HEIGHT-210),agentTexture,129,129,129*1,129*4),
    Entity(Vector2f(205,SCREEN_HEIGHT-210),agentTexture,129,129,129*2,129*4),
    Entity(Vector2f(210,SCREEN_HEIGHT-210),agentTexture,129,129,129*3,129*4),
    Entity(Vector2f(215,SCREEN_HEIGHT-210),agentTexture,129,129,129*4,129*4),
    Entity(Vector2f(215,SCREEN_HEIGHT-210),agentTexture,129,129,129*5,129*4),
    Entity(Vector2f(215,SCREEN_HEIGHT-210),agentTexture,129,129,129*6,129*4)
};

std::vector<Entity> running_enemy ={
    Entity(Vector2f(15,SCREEN_HEIGHT-210),enemyTexture,129,129,516,129),
    Entity(Vector2f(20,SCREEN_HEIGHT-210),enemyTexture,129,129,645,129),
    Entity(Vector2f(25,SCREEN_HEIGHT-210),enemyTexture,129,129,774,129),
    Entity(Vector2f(10,SCREEN_HEIGHT-210),enemyTexture,129,129,387,129)
};

Entity obstacleup = Entity(Vector2f(450,260),obstacleTexture,32,SCREEN_HEIGHT-215,0,0);
Entity obstacledown = Entity(Vector2f(450,0),obstacleTexture,32,SCREEN_HEIGHT-703,0,0);

Entity background = Entity(Vector2f(0,0),backTexture,2560,960,0,0);

// Entity scorecard = Entity(Vector2f(10,50),scoreTexture,text_w,text_h,0,0);
