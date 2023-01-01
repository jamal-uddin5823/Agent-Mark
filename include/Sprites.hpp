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
#define OBSTACLE_WIDTH 70
#define OBSTACLEJUMP_HEIGHT SCREEN_HEIGHT-215
#define OBSTACLESLIDE_HEIGHT SCREEN_HEIGHT-803
#define BACKGROUND_WIDTH 2560
#define BACKGROUNG_HEIGHT 960




RenderWindow window("Agent Mark", SCREEN_WIDTH,SCREEN_HEIGHT);

int blackBox_x=0,blackBox_y = SCREEN_HEIGHT/3-32;
SDL_Texture* blackBoxTexture = window.loadTexture("res/Obstacle.png",0,0,0,0); 
SDL_Texture* backTexture = window.loadTexture("res/skyline.png",1,255,255,255);
SDL_Texture* agentTexture = window.loadTexture("res/sheet.png",1,255,255,255);
SDL_Texture* enemyTexture = window.loadTexture("res/enemysheet.png",0,255,0,0);
SDL_Texture* obstacleTexture = window.loadTexture("res/Obstacle.png",0,0,0,0);
SDL_Texture* lifeTexture = window.loadTexture("res/life.png",0,0,0,0);
SDL_Texture* runTexture = window.loadTexture("res/run.png",0,0,0,0);
SDL_Texture* coinTexture = window.loadTexture("res/coin.png",0,0,0,0);
SDL_Texture* greyBoxTexture = window.loadTexture("res/Greybox.png",0,0,0,0);




SDL_Texture* first_pageTexture = window.loadTexture("res/mark.jpg",0,0,0,0);
SDL_Texture* countdownTexture = window.loadTexture("res/countdown_bg.png",0,0,0,0);

SDL_Texture* main_menuTexture = window.loadTexture("res/Mainmenu2.png",0,0,0,0);
SDL_Texture* new_gameTexture = window.loadTexture("res/MainmenuNewGame.png",0,0,0,0);
// SDL_Texture* new_gameTexture2 = window.loadTexture("res/newgame2.jpg",0,0,0,0);

SDL_Texture* load_gameTexture = window.loadTexture("res/Mainmenucontinue.png",0,0,0,0);
// SDL_Texture* load_gameTexture2 = window.loadTexture("res/loadgame2.jpg",0,0,0,0);

SDL_Texture* main_menu_high_scoreTexture = window.loadTexture("res/Mainmenuhighscore.png",0,0,0,0);
SDL_Texture* high_scoreTexture = window.loadTexture("res/highscore.png",0,0,0,0);

SDL_Texture* main_manu_optionsTexture = window.loadTexture("res/Mainmenuoptions.png",0,0,0,0);
SDL_Texture* optionsTexture1 = window.loadTexture("res/optionsunmute.png",0,0,0,0);
SDL_Texture* optionsTexture2 = window.loadTexture("res/optionsmute.png",0,0,0,0);

SDL_Texture* exitTexture = window.loadTexture("res/Mainmenuexit.png",0,0,0,0);
// SDL_Texture* exitTexture2 = window.loadTexture("res/exit2.jpg",0,0,0,0);
SDL_Texture* gameover = window.loadTexture("res/gameover.png",0,0,0,0);



std::vector<Entity> running_agent ={
    //                      position in screen                  position from sprite
    Entity(Vector2f(200,SCREEN_HEIGHT-210),agentTexture,SPRITE_DIM,SPRITE_DIM,SPRITE_DIM*3,SPRITE_DIM),
    Entity(Vector2f(205,SCREEN_HEIGHT-210),agentTexture,SPRITE_DIM,SPRITE_DIM,SPRITE_DIM*4,SPRITE_DIM),
    Entity(Vector2f(210,SCREEN_HEIGHT-210),agentTexture,SPRITE_DIM,SPRITE_DIM,SPRITE_DIM*5,SPRITE_DIM),
    Entity(Vector2f(215,SCREEN_HEIGHT-210),agentTexture,SPRITE_DIM,SPRITE_DIM,SPRITE_DIM*6,SPRITE_DIM)
};


std::vector<Entity> jumping_agent ={
    //                      position in screen                  position from sprite
    Entity(Vector2f(200,SCREEN_HEIGHT-210-120),agentTexture,SPRITE_DIM,SPRITE_DIM,SPRITE_DIM,SPRITE_DIM*3),
    Entity(Vector2f(200,SCREEN_HEIGHT-210-120),agentTexture,SPRITE_DIM,SPRITE_DIM,SPRITE_DIM*2,SPRITE_DIM*3),
    Entity(Vector2f(200,SCREEN_HEIGHT-210-120),agentTexture,SPRITE_DIM,SPRITE_DIM,SPRITE_DIM*3,SPRITE_DIM*3),
    Entity(Vector2f(200,SCREEN_HEIGHT-210-120),agentTexture,SPRITE_DIM,SPRITE_DIM,SPRITE_DIM*4,SPRITE_DIM*3),
    // Entity(Vector2f(200,SCREEN_HEIGHT-210-120),agentTexture,SPRITE_DIM,SPRITE_DIM,SPRITE_DIM*3,SPRITE_DIM*3),
    Entity(Vector2f(200,SCREEN_HEIGHT-210-120),agentTexture,SPRITE_DIM,SPRITE_DIM,SPRITE_DIM*2,SPRITE_DIM*3),
    // Entity(Vector2f(200,SCREEN_HEIGHT-210-120),agentTexture,SPRITE_DIM,SPRITE_DIM,SPRITE_DIM*5,SPRITE_DIM*3),
    Entity(Vector2f(200,SCREEN_HEIGHT-210-120),agentTexture,SPRITE_DIM,SPRITE_DIM,SPRITE_DIM*5,SPRITE_DIM*3),
    // Entity(Vector2f(200,SCREEN_HEIGHT-210-120),agentTexture,SPRITE_DIM,SPRITE_DIM,0,SPRITE_DIM*3)
    
};
std::vector<Entity> sliding_agent ={
    //                      position in screen                  position from sprite
    Entity(Vector2f(200,SCREEN_HEIGHT-210),agentTexture,SPRITE_DIM,SPRITE_DIM,SPRITE_DIM,SPRITE_DIM*4),
    Entity(Vector2f(205,SCREEN_HEIGHT-210),agentTexture,SPRITE_DIM,SPRITE_DIM,SPRITE_DIM*2,SPRITE_DIM*4),
    // Entity(Vector2f(210,SCREEN_HEIGHT-210),agentTexture,SPRITE_DIM,SPRITE_DIM,SPRITE_DIM*3,SPRITE_DIM*4),
    Entity(Vector2f(210,SCREEN_HEIGHT-210),agentTexture,SPRITE_DIM,SPRITE_DIM,SPRITE_DIM*3,SPRITE_DIM*4),
    Entity(Vector2f(215,SCREEN_HEIGHT-210),agentTexture,SPRITE_DIM,SPRITE_DIM,SPRITE_DIM*4,SPRITE_DIM*4),
    Entity(Vector2f(215,SCREEN_HEIGHT-210),agentTexture,SPRITE_DIM,SPRITE_DIM,SPRITE_DIM*5,SPRITE_DIM*4),
    Entity(Vector2f(215,SCREEN_HEIGHT-210),agentTexture,SPRITE_DIM,SPRITE_DIM,SPRITE_DIM*6,SPRITE_DIM*4)
};

std::vector<Entity> running_enemy ={
    //                      position in screen                  position from sprite
    Entity(Vector2f(15,SCREEN_HEIGHT-210),enemyTexture,SPRITE_DIM,SPRITE_DIM,SPRITE_DIM*4,SPRITE_DIM),
    Entity(Vector2f(20,SCREEN_HEIGHT-210),enemyTexture,SPRITE_DIM,SPRITE_DIM,SPRITE_DIM*5,SPRITE_DIM),
    Entity(Vector2f(25,SCREEN_HEIGHT-210),enemyTexture,SPRITE_DIM,SPRITE_DIM,SPRITE_DIM*6,SPRITE_DIM),
    Entity(Vector2f(10,SCREEN_HEIGHT-210),enemyTexture,SPRITE_DIM,SPRITE_DIM,SPRITE_DIM*3,SPRITE_DIM)
};

// Entity obstacleup = Entity(Vector2f(OBSTACLEX,OBSTACLEJUMPY),obstacleTexture,OBSTACLE_WIDTH,OBSTACLEJUMP_HEIGHT,0,0);

//                      position in screen                  position from sprite
Entity obstacle = Entity(Vector2f(1500,600),obstacleTexture,OBSTACLE_WIDTH,OBSTACLESLIDE_HEIGHT,0,0);
Entity obstacle2 = Entity(Vector2f(2250,600),obstacleTexture,OBSTACLE_WIDTH,OBSTACLESLIDE_HEIGHT,0,0);
std::vector<Entity> obstacle_array={obstacle,obstacle2};


//                      position in screen                  position from sprite
Entity background = Entity(Vector2f(0,0),backTexture,BACKGROUND_WIDTH,BACKGROUNG_HEIGHT,0,0);

//                      position in screen                                     position from sprite
Entity coin = Entity(Vector2f(SCREEN_WIDTH,SCREEN_HEIGHT-200),coinTexture,77,64,0,0);
Entity freerun = Entity(Vector2f(SCREEN_WIDTH,SCREEN_HEIGHT-200),runTexture,77,64,0,0);
Entity lifeline = Entity(Vector2f(SCREEN_WIDTH,SCREEN_HEIGHT-200),lifeTexture,77,64,0,0);



Entity firstpage = Entity(Vector2f(0,0),first_pageTexture,SCREEN_WIDTH,SCREEN_HEIGHT,0,0);
Entity countdownEntity = Entity(Vector2f(0,0),countdownTexture,SCREEN_WIDTH,SCREEN_HEIGHT,0,0);


Entity menu = Entity(Vector2f(0,0),main_menuTexture,SCREEN_WIDTH,SCREEN_HEIGHT,0,0);
Entity new_game = Entity(Vector2f(0,0),new_gameTexture,SCREEN_WIDTH,SCREEN_HEIGHT,0,0);
Entity load_game = Entity(Vector2f(0,0),load_gameTexture,SCREEN_WIDTH,SCREEN_HEIGHT,0,0);
Entity main_menu_high_score = Entity(Vector2f(0,0),main_menu_high_scoreTexture,SCREEN_WIDTH,SCREEN_HEIGHT,0,0);
Entity high_score = Entity(Vector2f(0,0),high_scoreTexture,SCREEN_WIDTH,SCREEN_HEIGHT,0,0);
Entity main_menu_options = Entity(Vector2f(0,0),main_manu_optionsTexture,SCREEN_WIDTH,SCREEN_HEIGHT,0,0);
Entity optionsUnmute = Entity(Vector2f(0,0),optionsTexture1,SCREEN_WIDTH,SCREEN_HEIGHT,0,0);
Entity optionsMute = Entity(Vector2f(0,0),optionsTexture2,SCREEN_WIDTH,SCREEN_HEIGHT,0,0);

Entity exit_game = Entity(Vector2f(0,0),exitTexture,SCREEN_WIDTH,SCREEN_HEIGHT,0,0);
Entity game_over = Entity(Vector2f(0,0),gameover,SCREEN_WIDTH,SCREEN_HEIGHT,0,0 );


