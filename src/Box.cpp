// #include<SDL2/SDL.h>
// #include<SDL2/SDL_image.h>
// #include<SDL2/SDL_timer.h>
// #include<SDL2/SDL_ttf.h>
// #include<SDL2/SDL_mixer.h>

// #include<iostream>

// #include "Box.hpp"

// #define SCREEN_WIDTH 1280
// #define SCREEN_HEIGHT 960

// Box::Box()
// {
	
// 	int options=rand()%2;
// 	float vals;
// 	if(options==0)vals= 0.6;
// 	else vals=0.4;
//     //Initialize the offsets
//     mPosX = SCREEN_WIDTH;
//     mPosY = (vals)*SCREEN_HEIGHT;
//     //Initialize the velocity
//     mVelX = BOX_VEL;
// }

// void Box::move()
// {
//     //Move the dot left or right
//     mPosX -= mVelX;  
// }

// void Box::render(SDL_Rect* clip )
// {
// //Set rendering space and render to screen
// 	SDL_Rect renderQuad = { mPosX, mPosY, BOX_WIDTH, BOX_HEIGHT };

// 	//Set clip rendering dimensions
// 	if( clip != NULL )
// 	{
// 		renderQuad.w = clip->w;
// 		renderQuad.h = clip->h;
// 	}

// 	//Render to screen
// 	SDL_RenderCopy( renderer, mTexture, clip, &renderQuad );
// }