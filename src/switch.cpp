// #include "switch.hpp"

// #include "RenderWindow.hpp"

// LTexture::LTexture()
// {
// 	//Initialize
// 	mTexture = NULL;
// 	mWidth = 0;
// 	mHeight = 0;
// }

// LTexture::~LTexture()
// {
// 	//Deallocate
// 	free();
// }
// bool LTexture::loadFromFile( std::string path )
// {
// 	//Get rid of preexisting texture
// 	free();

// 	//The final texture
// 	SDL_Texture* newTexture = NULL;

// 	//Load image at specified path
// 	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
// 	if( loadedSurface == NULL )
// 	{
// 		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
// 	}
// 	else
// 	{
// 		//Color key image
// 		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

// 		//Create texture from surface pixels
//         newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
// 		if( newTexture == NULL )
// 		{
// 			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
// 		}
// 		else
// 		{
// 			//Get image dimensions
// 			mWidth = loadedSurface->w;
// 			mHeight = loadedSurface->h;
// 		}

// 		//Get rid of old loaded surface
// 		SDL_FreeSurface( loadedSurface );
// 	}

// 	//Return success
// 	mTexture = newTexture;
// 	return mTexture != NULL;
// }

// void LTexture::free()
// {
// 	//Free texture if it exists
// 	if( mTexture != NULL )
// 	{
// 		SDL_DestroyTexture( mTexture );
// 		mTexture = NULL;
// 		mWidth = 0;
// 		mHeight = 0;
// 	}
// }
// void LTexture::renderjump( int x, int y, int frameNumber,  SDL_Rect* clip )
// {
// 	//Set rendering space and render to screen
// 	if(frameNumber>=4)frameNumber=6-frameNumber;
// 	SDL_Rect renderQuad = { x, y-40*frameNumber, mWidth, mHeight };

// 	//Set clip rendering dimensions
// 	if( clip != NULL )
// 	{
// 		renderQuad.w = clip->w;
// 		renderQuad.h = clip->h;
// 	}

// 	//Render to screen
// 	SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
// }

// void LTexture::renderSlideAndRun(int x, int y, SDL_Rect* clip)
// {
// 	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

// 	//Set clip rendering dimensions
// 	if( clip != NULL )
// 	{
// 		renderQuad.w = clip->w;
// 		renderQuad.h = clip->h;
// 	}

// 	//Render to screen
// 	SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
// }


// int LTexture::getWidth()
// {
// 	return mWidth;
// }

// int LTexture::getHeight()
// {
// 	return mHeight;
// }

// bool init()
// {
// 	//Initialization flag
// 	bool success = true;

// 	//Initialize SDL
// 	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
// 	{
// 		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
// 		success = false;
// 	}
// 	else
// 	{
// 		//Set texture filtering to linear
// 		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
// 		{
// 			printf( "Warning: Linear texture filtering not enabled!" );
// 		}

// 		//Create window
// 		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
// 		if(gWindow == NULL )
// 		{
// 			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
// 			success = false;
// 		}
// 		else
// 		{
// 			//Create vsynced renderer for window
// 			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
// 			if( gRenderer == NULL )
// 			{
// 				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
// 				success = false;
// 			}
// 			else
// 			{
// 				//Initialize renderer color
// 				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

// 				//Initialize PNG loading
// 				int imgFlags = IMG_INIT_PNG;
// 				if( !( IMG_Init( imgFlags ) & imgFlags ) )
// 				{
// 					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
// 					success = false;
// 				}
// 			}
// 		}
// 	}

// 	return success;
// }

// bool loadMedia()
// {
// 	//Loading success flag
// 	bool success = true;

// 	//Load sprite sheet texture
// 	if( !gSpriteSheetTexture.loadFromFile( "sprite.png" ) )
// 	{
// 		printf( "Failed to load walking animation texture!\n" );
// 		success = false;
// 	}
// 	else
// 	{
// 		//Set jumping sprite clips
// 		JumpingSpriteClips[ 0 ].x =   129*1;
// 		JumpingSpriteClips[ 0 ].y =   129*2;
// 		JumpingSpriteClips[ 0 ].w =  129;
// 		JumpingSpriteClips[ 0 ].h = 129;

// 		JumpingSpriteClips[ 1 ].x =  129*3;
// 		JumpingSpriteClips[ 1 ].y =  129*3;
// 		JumpingSpriteClips[ 1 ].w =  129;
// 		JumpingSpriteClips[ 1 ].h = 129;
		
// 		JumpingSpriteClips[ 2 ].x = 129*4;
// 		JumpingSpriteClips[ 2 ].y =   129*3;
// 		JumpingSpriteClips[ 2 ].w =  129;
// 		JumpingSpriteClips[ 2 ].h = 129;

// 		JumpingSpriteClips[ 3 ].x = 129*5;
// 		JumpingSpriteClips[ 3 ].y =  129*3;
// 		JumpingSpriteClips[ 3 ].w =  129;
// 		JumpingSpriteClips[ 3 ].h = 129;
		
// 		JumpingSpriteClips[ 4 ].x =   129*6;
// 		JumpingSpriteClips[ 4 ].y =   129*3;
// 		JumpingSpriteClips[ 4 ].w =  129;
// 		JumpingSpriteClips[ 4 ].h = 129;
		
// 		JumpingSpriteClips[ 5 ].x =   0;
// 		JumpingSpriteClips[ 5 ].y =   129*3;
// 		JumpingSpriteClips[ 5 ].w =  129;
// 		JumpingSpriteClips[ 5 ].h = 129;
		
// 		JumpingSpriteClips[ 6 ].x =   129;
// 		JumpingSpriteClips[ 6 ].y =   129*1;
// 		JumpingSpriteClips[ 6 ].w =  129;
// 		JumpingSpriteClips[ 6 ].h = 129;
		


// 		//Set Sliding sprite clips
// 		SlidingSpriteClips[ 0 ].x =   129*1;
// 		SlidingSpriteClips[ 0 ].y =   129*2;
// 		SlidingSpriteClips[ 0 ].w =  129;
// 		SlidingSpriteClips[ 0 ].h = 129;

// 		SlidingSpriteClips[ 1 ].x =  0;
// 		SlidingSpriteClips[ 1 ].y =  129*4;
// 		SlidingSpriteClips[ 1 ].w =  129;
// 		SlidingSpriteClips[ 1 ].h = 129;
		
// 		SlidingSpriteClips[ 2 ].x = 129*1;
// 		SlidingSpriteClips[ 2 ].y =   129*4;
// 		SlidingSpriteClips[ 2 ].w =  129;
// 		SlidingSpriteClips[ 2 ].h = 129;

// 		SlidingSpriteClips[ 3 ].x = 129*2;
// 		SlidingSpriteClips[ 3 ].y =  129*4;
// 		SlidingSpriteClips[ 3 ].w =  129;
// 		SlidingSpriteClips[ 3 ].h = 129;
		
// 		SlidingSpriteClips[ 4 ].x =   129*3;
// 		SlidingSpriteClips[ 4 ].y =   129*4;
// 		SlidingSpriteClips[ 4 ].w =  129;
// 		SlidingSpriteClips[ 4 ].h = 129;
		
// 		SlidingSpriteClips[ 5 ].x =   129*4;
// 		SlidingSpriteClips[ 5 ].y =   129*4;
// 		SlidingSpriteClips[ 5 ].w =  129;
// 		SlidingSpriteClips[ 5 ].h = 129;
		
// 		SlidingSpriteClips[ 6 ].x =   129*5;
// 		SlidingSpriteClips[ 6 ].y =   129*4;
// 		SlidingSpriteClips[ 6 ].w =  129;
// 		SlidingSpriteClips[ 6 ].h = 129;
		
// 		SlidingSpriteClips[ 7 ].x =   129*6;
// 		SlidingSpriteClips[ 7 ].y =   129*4;
// 		SlidingSpriteClips[ 7 ].w =  129;
// 		SlidingSpriteClips[ 7 ].h = 129;
		
// 		SlidingSpriteClips[ 8 ].x =   129*1;
// 		SlidingSpriteClips[ 8 ].y =   129*3;
// 		SlidingSpriteClips[ 8 ].w =  129;
// 		SlidingSpriteClips[ 8 ].h = 129;
		
// 		//Set running sprite clips

// 		RunningSpriteClips[ 0 ].x =   129*3;
// 		RunningSpriteClips[ 0 ].y =   129*1;
// 		RunningSpriteClips[ 0 ].w =  129;
// 		RunningSpriteClips[ 0 ].h = 129;

// 		RunningSpriteClips[ 1 ].x =   129*4;
// 		RunningSpriteClips[ 1 ].y =   129*1;
// 		RunningSpriteClips[ 1 ].w =  129;
// 		RunningSpriteClips[ 1 ].h = 129;

// 		RunningSpriteClips[ 2 ].x =   129*5;
// 		RunningSpriteClips[ 2 ].y =   129*1;
// 		RunningSpriteClips[ 2 ].w =  129;
// 		RunningSpriteClips[ 2 ].h = 129;

// 		RunningSpriteClips[ 3 ].x =   129*6;
// 		RunningSpriteClips[ 3 ].y =   129*1;
// 		RunningSpriteClips[ 3 ].w =  129;
// 		RunningSpriteClips[ 3 ].h = 129;

// 		RunningSpriteClips[ 4 ].x =   129*0;
// 		RunningSpriteClips[ 4 ].y =   129*2;
// 		RunningSpriteClips[ 4 ].w =  129;
// 		RunningSpriteClips[ 4 ].h = 129;

// 		RunningSpriteClips[ 5 ].x =   129*0;
// 		RunningSpriteClips[ 5 ].y =   129*3;
// 		RunningSpriteClips[ 5 ].w =  129;
// 		RunningSpriteClips[ 5 ].h = 129;		


		
// 	}
	
// 	return success;
// }

// void close()
// {
// 	//Free loaded images
// 	gSpriteSheetTexture.free();

// 	//Destroy window	
// 	SDL_DestroyRenderer( gRenderer );
// 	SDL_DestroyWindow( gWindow );
// 	gWindow = NULL;
// 	gRenderer = NULL;

// 	//Quit SDL subsystems
// 	IMG_Quit();
// 	SDL_Quit();
// }


// void LTexture::handleEvent(SDL_Event& e){
//     // int agent_frame=0;
//     if(e.type==SDL_KEYDOWN && e.key.repeat==0){
//         switch (e.key.keysym.sym)
//         {
//         case SDLK_UP:

//         while(1)
//         {
//             SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
//             SDL_RenderClear( gRenderer );
//             //Render current frame
//             SDL_Rect* currentClip = &JumpingSpriteClips[ frame / 18];
//             int frameNumber=frame/18;
//             gSpriteSheetTexture.renderjump( ( SCREEN_WIDTH - currentClip->w ) / 2, ( SCREEN_HEIGHT - currentClip->h ) / 2, frameNumber, currentClip );

//             //Update screen
//             SDL_RenderPresent( gRenderer );

//             //Go to next frame
//             ++frame;
//             //break animation
//             if( frame / 18 >= JUMPING_ANIMATION_FRAMES )
//             {
//                 break;
//             }
//         }

        

//         case SDLK_DOWN:

//         while(1)
//         {
//             SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
//             SDL_RenderClear( gRenderer );

//             //Render current frame
//             SDL_Rect* currentClip = &SlidingSpriteClips[ frame / 18];
//             int frameNumber=frame/18;
//             gSpriteSheetTexture.renderSlideAndRun( ( SCREEN_WIDTH - currentClip->w ) / 2, ( SCREEN_HEIGHT - currentClip->h ) / 2, currentClip );

//             //Update screen
//             SDL_RenderPresent( gRenderer );

//             //Go to next frame
//             ++frame;

//             //Break animation
//             if( frame / 18 >= SLIDING_ANIMATION_FRAMES )
//             {
//                 break;
//             }
//         }
//         default:
//         while(1)
//         {
//             SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
//             SDL_RenderClear( gRenderer );

//             //Render current frame
//             SDL_Rect* currentClip = &RunningSpriteClips[ frame / 18];
//             int frameNumber=frame/18;
//             gSpriteSheetTexture.renderSlideAndRun( ( SCREEN_WIDTH - currentClip->w ) / 2, ( SCREEN_HEIGHT - currentClip->h ) / 2, currentClip );

//             //Update screen
//             SDL_RenderPresent( gRenderer );

//             //Go to next frame
//             ++frame;

//             //Cycle animation
//             if( frame / 18 >= RUNNING_ANIMATION_FRAMES )
//             {
//                 break;
//             }
//         }


//         case SDLK_LEFT:
//             vel_x-=VELOCITY;
//             break;
//         case SDLK_RIGHT:

//             vel_x+=VELOCITY;
//             break;
//         }
//     }
    

// }
