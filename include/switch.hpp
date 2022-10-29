// #pragma once

// #include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>
// #include <stdio.h>
// #include <string>

// #include "RenderWindow.hpp"


// //Screen dimension constants
// const int SCREEN_WIDTH = 640;
// const int SCREEN_HEIGHT = 480;

// enum KeyPressSurfaces
// {
// 	KEY_PRESS_SURFACE_DEFAULT,
// 	KEY_PRESS_SURFACE_UP,
// 	KEY_PRESS_SURFACE_DOWN,
// 	KEY_PRESS_SURFACE_TOTAL
// };

// class LTexture
// {
// 	public:
// 		//Initializes variables
// 		LTexture();

// 		//Deallocates memory
// 		~LTexture();

// 		//Loads image at specified path
// 		bool loadFromFile( std::string path );

// 		//Deallocates texture
// 		void free();
// 		void renderjump( int x, int y, int frameNumber, SDL_Rect* clip = NULL );
// 		void renderSlideAndRun(int x, int y, SDL_Rect* clip= NULL);
//         std::pair<int,int> handleEvent(SDL_Event& e);
// 		//Gets image dimensions
// 		int getWidth();
// 		int getHeight();

// 	private:
// 		//The actual hardware texture
// 		SDL_Texture* mTexture;

// 		//Image dimensions
// 		int mWidth;
// 		int mHeight;
// };

// bool init();

// //Loads media
// bool loadMedia();

// //Frees media and shuts down SDL
// void close();
// int frame =0;

// // //The window we'll be rendering to
// SDL_Window* gWindow = NULL;

// //The window renderer
// SDL_Renderer* gRenderer = NULL;

// const int JUMPING_ANIMATION_FRAMES = 7, SLIDING_ANIMATION_FRAMES=9, RUNNING_ANIMATION_FRAMES=6;
// SDL_Rect JumpingSpriteClips[ JUMPING_ANIMATION_FRAMES], SlidingSpriteClips[SLIDING_ANIMATION_FRAMES], RunningSpriteClips[RUNNING_ANIMATION_FRAMES];
// LTexture gSpriteSheetTexture;

// //SDL_Surface gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];



// int main( int argc, char* args[] )
// {
// 	//Start up SDL and create window
// 	if( !init() )
// 	{
// 		printf( "Failed to initialize!\n" );
// 	}
// 	else
// 	{
// 		//Load media
// 		if( !loadMedia() )
// 		{
// 			printf( "Failed to load media!\n" );
// 		}
// 		else
// 		{	
// 			//Main loop flag
// 			bool quit = false;

// 			//Event handler
// 			SDL_Event e;

// 			//gCurrentSurface= gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];
// 			//Current animation frame
// 			int frame = 0;

// 			//While application is running
// 			while( !quit )
// 			{
// 				//Handle events on queue
// 				while( SDL_PollEvent( &e ) != 0 )
// 				{
// 					//User requests quit
// 					if( e.type == SDL_QUIT )
// 					{
// 						quit = true;
// 					}
					
// 				}

// 						SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
// 						SDL_RenderClear( gRenderer );

// 								//Render current frame
// 						SDL_Rect* currentClip = &RunningSpriteClips[ frame / 18];
// 						int frameNumber=frame/18;
// 						gSpriteSheetTexture.renderSlideAndRun( ( SCREEN_WIDTH - currentClip->w ) / 2, ( SCREEN_HEIGHT - currentClip->h ) / 2, currentClip );

// 						//Update screen
// 						SDL_RenderPresent( gRenderer );

// 						//Go to next frame
// 						++frame;

// 						//Cycle animation
// 						if( frame / 18 >= RUNNING_ANIMATION_FRAMES )
// 						{
// 							frame = 0;
// 						}
				
// 			}
// 		}
// 	}

// 	//Free resources and close SDL
// 	close();

// 	return 0;
// }


