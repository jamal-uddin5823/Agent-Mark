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

#define NEW_GAME false
#define CONTINUE_PREV_GAME true

//Button constants
const int BUTTON_WIDTH = 332;
const int BUTTON_HEIGHT = 97;

enum{
    WELCOME_SCREEN,
    MAIN_MENU,
    GAMEPLAY
};
enum Buttontypes{
	NEW_GAMEBUTTON=1,
	LOAD_GAMEBUTTON=2,
	HIGHSCOREBUTTON=3,
	OPTIONSBUTTON=4,
	EXITBUTTON=5,
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


void handleMouseEvent(SDL_Event &e, int buttonx, int buttony, int button, bool& gameRunning){
	    //If mouse event happened
    Entity currentSprite=menu;
	if( e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP )
	{
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
				// case SDL_MOUSEMOTION:
				// if(button == NEW_GAMEBUTTON)
				// 	currentSprite = new_game;
				// else if(button == LOAD_GAMEBUTTON)
				// 	currentSprite = load_game;
				// else if(button == HIGHSCOREBUTTON)
				// 	currentSprite = high_score;
				// else if(button == OPTIONSBUTTON)
				// 	currentSprite = options;
				// else if(button == EXITBUTTON)
				// 	currentSprite = exit_game;
				// break;
			

				case SDL_MOUSEBUTTONDOWN:
				if(button == NEW_GAMEBUTTON){
					game_status=GAMEPLAY;
					continue_flag=NEW_GAME;
				}
				else if(button == LOAD_GAMEBUTTON){
					game_status=GAMEPLAY;
					continue_flag=CONTINUE_PREV_GAME;
					// init_score_life();
				}
				else if(button == EXITBUTTON){
					gameRunning = false;
				}
				break;
			}
		}
	}
}