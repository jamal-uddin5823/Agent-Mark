#pragma once

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_timer.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_mixer.h>

#include<iostream>
#include<string>
#include<vector>

#include "Entity.hpp"
#include "Sprites.hpp"
#include "Gamefuncs.hpp"

#define NEW_GAME false
#define CONTINUE_PREV_GAME true

//Button constants
const int BUTTON_WIDTH = 332;
const int BUTTON_HEIGHT = 97;

bool mute=false;

// enum{
//     WELCOME_SCREEN,
//     MAIN_MENU,
// 	NEWGAMEPLAY,
//     LOADGAMEPLAY,
// 	GAMEOVER,
// 	HIGHSCORE,
// 	OPTIONS
// };
enum Buttontypes{
	NEW_GAMEBUTTON=1,
	LOAD_GAMEBUTTON=2,
	HIGHSCOREBUTTON=3,
	OPTIONSBUTTON=4,
	EXITBUTTON=5,
	GAMEOVERBUTTON=6,
	BACKBUTTON=7,
	MUSICBUTTON=8
};


enum ButtonSprite
{
	BUTTON_SPRITE_MOUSE_OUT = 0,
	BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
	BUTTON_SPRITE_MOUSE_DOWN = 2,
	BUTTON_SPRITE_MOUSE_UP = 3,
	BUTTON_SPRITE_TOTAL = 4
};




extern int game_status;
extern bool continue_flag;


void handleMouseEvent(SDL_Event &e, int buttonx, int buttony, int button_length, int button_width,int button, bool& gameRunning){
	    //If mouse event happened
	if( e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP )
	{
		Entity currentSprite = menu;
		//Get mouse position
		int x, y;
		SDL_GetMouseState( &x, &y );

		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if( x < buttonx)
		{
			inside = false;
		}
		//Mouse is right of the button
		else if( x > buttonx+BUTTON_WIDTH)
		{
			inside = false;
		}
		//Mouse above the button
		else if( y < buttony)
		{
			inside = false;
		}
		//Mouse below the button
		else if( y > buttony+BUTTON_HEIGHT )
		{
			inside = false;
		}

		//Mouse is outside button
		if( !inside )
		{
			currentSprite = menu;
		}
		//Mouse is inside button
		else
		{
			//Set mouse over sprite
			switch( e.type )
			{

				case SDL_MOUSEBUTTONDOWN:
				if(button == NEW_GAMEBUTTON){
					game_status=NEWGAMEPLAY;
					continue_flag=NEW_GAME;
					init_score_life(game_status);
					// std::cout<<score<<" "<<life<<'\n';
					score=0,life=3,initial_score=0;
				}
				else if(button == LOAD_GAMEBUTTON){
					game_status=LOADGAMEPLAY;
					continue_flag=CONTINUE_PREV_GAME;
					init_score_life(game_status);
				}
				else if(button == HIGHSCOREBUTTON){
					game_status = HIGHSCORE;
					highscoreshow();
				}
				else if(button== OPTIONSBUTTON){
					game_status= OPTIONS;
				}
				else if(button == EXITBUTTON){
					gameRunning = false;
				}
				else if(button == GAMEOVERBUTTON){
					game_status=MAIN_MENU;
				}
				else if(button == BACKBUTTON){
					game_status=MAIN_MENU;
				}
				else if(button== MUSICBUTTON){
					mute = !mute;
				}
				break;
			}
		}
	}
}
