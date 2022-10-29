#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_timer.h>
#include<iostream>
#include<string>

#include "Box.hpp"
#include "RenderWindow.hpp"

Box::Box()
{
 
	int options=rand()%2;
	float vals;
	if(options==0)vals= 0.6;
	else vals=0.4;
    //Initialize the offsets
    mPosX = SCREEN_WIDTH;
    mPosY = (vals)*SCREEN_HEIGHT;
    //Initialize the velocity
    mVelX = BOX_VEL;
}
 
void Box::move()
{
    //Move the dot left or right
    mPosX -= mVelX;
}
 
void Box::render()
{
    //Show the dot
	
}