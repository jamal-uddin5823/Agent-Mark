#pragma once

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_timer.h>
#include<iostream>
#include<string>
#include<vector>

#include "RenderWindow.hpp"
#include "Entity.hpp"

RenderWindow window("Agent Mark", SCREEN_WIDTH,SCREEN_HEIGHT);

int blackBox_x=0,blackBox_y = SCREEN_HEIGHT/3-32;
SDL_Texture* blackBoxTexture = window.loadTexture("res/Blackbox.png",0,0,0,0); 
SDL_Texture* backTexture = window.loadTexture("res/background.jpg",1,255,255,255);
SDL_Texture* agentTexture = window.loadTexture("res/sprite.png",1,255,255,255);
SDL_Texture* enemyTexture = window.loadTexture("res/sprite.png",1,255,255,255); 




Entity standing_boy = Entity(Vector2f(100,SCREEN_HEIGHT-210),agentTexture,125,125,0,0);

std::vector<Entity> running_agent ={
    // Entity(Vector2f(0,SCREEN_HEIGHT-200),agentTexture,125,125,0,0),
    // Entity(Vector2f(0,SCREEN_HEIGHT-200),agentTexture,125,125,250,125),
    Entity(Vector2f(200,SCREEN_HEIGHT-210),agentTexture,129,129,387,129),
    Entity(Vector2f(205,SCREEN_HEIGHT-210),agentTexture,129,129,516,129),
    Entity(Vector2f(210,SCREEN_HEIGHT-210),agentTexture,129,129,645,129),
    Entity(Vector2f(215,SCREEN_HEIGHT-210),agentTexture,129,129,774,129)
};

std::vector<Entity> running_enemy ={
    // Entity(Vector2f(0,SCREEN_HEIGHT-200),agentTexture,125,125,0,0),
    // Entity(Vector2f(0,SCREEN_HEIGHT-200),agentTexture,125,125,250,125),
    Entity(Vector2f(15,SCREEN_HEIGHT-210),agentTexture,129,129,516,129),
    Entity(Vector2f(20,SCREEN_HEIGHT-210),agentTexture,129,129,645,129),
    Entity(Vector2f(25,SCREEN_HEIGHT-210),agentTexture,129,129,774,129),
    Entity(Vector2f(10,SCREEN_HEIGHT-210),agentTexture,129,129,387,129)
};

Entity background = Entity(Vector2f(0,0),backTexture,612,394,0,0);
