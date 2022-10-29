#pragma once

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_timer.h>
#include<iostream>
#include<string>

class Box
{
    public:
		//The dimensions of the dot
		static const int BOX_WIDTH = 100;
		static const int BOX_HEIGHT = 30;

		//Maximum axis velocity of the dot
		static const int BOX_VEL = 5;

		//Initializes the variables
		Box();

		//Moves the dot
		void move();

		//Shows the dot on the screen
		void render();

    private:
		//The X and Y offsets of the dot
		int mPosX, mPosY;

		//The velocity of the dot
		int mVelX, mVelY;
};