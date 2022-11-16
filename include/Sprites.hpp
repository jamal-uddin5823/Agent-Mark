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


#define SPRITE_DIM 129
#define OBSTACLEX 450
#define OBSTACLEJUMPY 260
#define OBSTACLESLIDEY 100
#define OBSTACLE_WIDTH 32
#define OBSTACLEJUMP_HEIGHT SCREEN_HEIGHT-215
#define OBSTACLESLIDE_HEIGHT SCREEN_HEIGHT-803
#define BACKGROUND_WIDTH 2560
#define BACKGROUNG_HEIGHT 960




RenderWindow window("Agent Mark", SCREEN_WIDTH,SCREEN_HEIGHT);

int blackBox_x=0,blackBox_y = SCREEN_HEIGHT/3-32;
SDL_Texture* blackBoxTexture = window.loadTexture("res/Blackbox.png",0,0,0,0); 
SDL_Texture* backTexture = window.loadTexture("res/skyline.png",1,255,255,255);
SDL_Texture* agentTexture = window.loadTexture("res/sheet.png",1,255,255,255);
SDL_Texture* enemyTexture = window.loadTexture("res/enemysheet.png",0,255,0,0);
SDL_Texture* obstacleTexture = window.loadTexture("res/Blackbox.png",0,0,0,0);
SDL_Texture* lifeTexture = window.loadTexture("res/lifeline.png",0,0,0,0);










Entity standing_boy = Entity(Vector2f(100,SCREEN_HEIGHT-210),agentTexture,125,125,0,0);

Entity newgrass = Entity(Vector2f(blackBox_x,blackBox_y),blackBoxTexture,32,32,0,0);



std::vector<Entity> running_agent ={
    Entity(Vector2f(200,SCREEN_HEIGHT-210),agentTexture,SPRITE_DIM,SPRITE_DIM,SPRITE_DIM*3,SPRITE_DIM),
    Entity(Vector2f(205,SCREEN_HEIGHT-210),agentTexture,SPRITE_DIM,SPRITE_DIM,SPRITE_DIM*4,SPRITE_DIM),
    Entity(Vector2f(210,SCREEN_HEIGHT-210),agentTexture,SPRITE_DIM,SPRITE_DIM,SPRITE_DIM*5,SPRITE_DIM),
    Entity(Vector2f(215,SCREEN_HEIGHT-210),agentTexture,SPRITE_DIM,SPRITE_DIM,SPRITE_DIM*6,SPRITE_DIM)
};


std::vector<Entity> jumping_agent ={
    Entity(Vector2f(200,SCREEN_HEIGHT-210),agentTexture,SPRITE_DIM,SPRITE_DIM,SPRITE_DIM*2,SPRITE_DIM*3),
    Entity(Vector2f(200,SCREEN_HEIGHT-210),agentTexture,SPRITE_DIM,SPRITE_DIM,SPRITE_DIM*3,SPRITE_DIM*3),
    Entity(Vector2f(200,SCREEN_HEIGHT-210),agentTexture,SPRITE_DIM,SPRITE_DIM,SPRITE_DIM*3,SPRITE_DIM*3),
    Entity(Vector2f(200,SCREEN_HEIGHT-210),agentTexture,SPRITE_DIM,SPRITE_DIM,SPRITE_DIM*4,SPRITE_DIM*3),
    Entity(Vector2f(200,SCREEN_HEIGHT-210),agentTexture,SPRITE_DIM,SPRITE_DIM,SPRITE_DIM*5,SPRITE_DIM*3)
    
};
std::vector<Entity> sliding_agent ={
    Entity(Vector2f(200,SCREEN_HEIGHT-210),agentTexture,SPRITE_DIM,SPRITE_DIM,SPRITE_DIM,SPRITE_DIM*4),
    Entity(Vector2f(205,SCREEN_HEIGHT-210),agentTexture,SPRITE_DIM,SPRITE_DIM,SPRITE_DIM*2,SPRITE_DIM*4),
    Entity(Vector2f(210,SCREEN_HEIGHT-210),agentTexture,SPRITE_DIM,SPRITE_DIM,SPRITE_DIM*3,SPRITE_DIM*4),
    Entity(Vector2f(215,SCREEN_HEIGHT-210),agentTexture,SPRITE_DIM,SPRITE_DIM,SPRITE_DIM*4,SPRITE_DIM*4),
    Entity(Vector2f(215,SCREEN_HEIGHT-210),agentTexture,SPRITE_DIM,SPRITE_DIM,SPRITE_DIM*5,SPRITE_DIM*4),
    Entity(Vector2f(215,SCREEN_HEIGHT-210),agentTexture,SPRITE_DIM,SPRITE_DIM,SPRITE_DIM*6,SPRITE_DIM*4)
};

std::vector<Entity> running_enemy ={
    Entity(Vector2f(15,SCREEN_HEIGHT-210),enemyTexture,SPRITE_DIM,SPRITE_DIM,SPRITE_DIM*4,SPRITE_DIM),
    Entity(Vector2f(20,SCREEN_HEIGHT-210),enemyTexture,SPRITE_DIM,SPRITE_DIM,SPRITE_DIM*5,SPRITE_DIM),
    Entity(Vector2f(25,SCREEN_HEIGHT-210),enemyTexture,SPRITE_DIM,SPRITE_DIM,SPRITE_DIM*6,SPRITE_DIM),
    Entity(Vector2f(10,SCREEN_HEIGHT-210),enemyTexture,SPRITE_DIM,SPRITE_DIM,SPRITE_DIM*3,SPRITE_DIM)
};

Entity obstacleup = Entity(Vector2f(OBSTACLEX,OBSTACLEJUMPY),obstacleTexture,OBSTACLE_WIDTH,OBSTACLEJUMP_HEIGHT,0,0);
Entity obstacledown = Entity(Vector2f(OBSTACLEX,OBSTACLESLIDEY),obstacleTexture,OBSTACLE_WIDTH,OBSTACLESLIDE_HEIGHT,0,0);

Entity background = Entity(Vector2f(0,0),backTexture,BACKGROUND_WIDTH,BACKGROUNG_HEIGHT,0,0);
Entity lifeline = Entity(Vector2f(SCREEN_WIDTH,SCREEN_HEIGHT/2-100),lifeTexture,32,32,0,0);

