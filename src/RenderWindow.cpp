#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_timer.h>
#include<iostream>

#include "RenderWindow.hpp"
#include "Entity.hpp"

RenderWindow::RenderWindow(std::string p_title, int p_w, int p_h){
    
    window = SDL_CreateWindow(p_title.c_str(),SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
    p_w,p_h,SDL_WINDOW_SHOWN);

    if(window==NULL){
        std::cout<<"Window failed"<<'\n';
    }

    Uint32 renderflags = SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC;
    renderer = SDL_CreateRenderer(window,-1,renderflags);

    if(renderer == NULL){
        std::cout<<"Renderer Failed"<<'\n';
    }
}

SDL_Texture* RenderWindow::loadTexture(std::string p_filepath, bool flag,Uint8 r, Uint8 g,Uint8 b){
    SDL_Surface* surface = NULL;
    SDL_Texture* texture = NULL;

    surface = IMG_Load(p_filepath.c_str());
    if(surface ==NULL){
        std::cout<<"Surface failed. "<<SDL_GetError()<<'\n';
    }
    if(flag==1){
        SDL_SetColorKey(surface,SDL_TRUE,SDL_MapRGB(surface->format,r,g,b));
    }
    texture = SDL_CreateTextureFromSurface(renderer,surface);
    if(texture ==NULL){
        std::cout<<"Texture failed. "<<SDL_GetError()<<'\n';
    }

    return texture;

}


void RenderWindow::cleanUp(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}


void RenderWindow::clearScreen(){
    SDL_RenderClear(renderer);
}

void RenderWindow::changeRenderColor(int r,int g, int b, int a){
    SDL_SetRenderDrawColor(renderer,r,g,b,a);
}

void RenderWindow::render(Entity &p_entity,double times){
    SDL_Rect src;
    src.x = p_entity.getCurrentFrame().x;
    src.y = p_entity.getCurrentFrame().y;
    src.w = p_entity.getCurrentFrame().w;
    src.h = p_entity.getCurrentFrame().h;

    SDL_Rect dest;
    dest.x = p_entity.getpos().x*times;
    dest.y = p_entity.getpos().y*times;
    dest.w = p_entity.getCurrentFrame().w*times;
    dest.h = p_entity.getCurrentFrame().h*times;


    SDL_RenderCopy(renderer,p_entity.getTex(),&src,&dest);
}


void RenderWindow::renderBG( int x, int y,Entity background, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, background.getCurrentFrame().w, background.getCurrentFrame().h };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( renderer, background.getTex(), clip, &renderQuad, angle, center, flip );
}

void RenderWindow::renderjump(Entity a,int frameNumber)
{
	//Set rendering space and render to screen
	if(frameNumber>=2)frameNumber=4-frameNumber;
	// SDL_Rect renderQuad = { a.getCurrentFrame().x, a.getCurrentFrame().y-40*frameNumber, a.getCurrentFrame().w, a.getCurrentFrame().h };
 
	SDL_Rect src;
    src.x = a.getCurrentFrame().x;
    src.y = a.getCurrentFrame().y;
    src.w = a.getCurrentFrame().w;
    src.h = a.getCurrentFrame().h;

    SDL_Rect dest;
    dest.x = a.getpos().x;
    dest.y = a.getpos().y-90*frameNumber;
    dest.w = a.getCurrentFrame().w;
    dest.h = a.getCurrentFrame().h;
	//Render to screen
	SDL_RenderCopy(renderer, a.getTex(), &src, &dest );
}


void RenderWindow::display(){
    SDL_RenderPresent(renderer);
}