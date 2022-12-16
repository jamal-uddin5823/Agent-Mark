#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_timer.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_mixer.h>


#include<iostream>

#include "RenderWindow.hpp"
#include "Entity.hpp"


// static int OBSTACLE_SPEED =-10;
int threshold=10;
int time_passed=0;


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

SDL_Texture* RenderWindow::Textload(std::string textureText,std::string fontpath,int fontsize, Uint8 r, Uint8 g, Uint8 b, int* w, int* h){
    if( TTF_Init() <0 )
    {
        std::cout<< "SDL_ttf could not initialize! SDL_ttf Error: "<< TTF_GetError() <<'\n';
    }
    TTF_Font* font= TTF_OpenFont(fontpath.c_str(),fontsize);
    SDL_Color textColor = {r,g,b};
    SDL_Texture* texture=NULL;
    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid( font, textureText.c_str(), textColor );
    if( textSurface == NULL )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    
    //Create texture from surface pixels
    texture = SDL_CreateTextureFromSurface( renderer, textSurface );
    if( texture == NULL )
    {
        printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
    }
    SDL_FreeSurface(textSurface);
    
    SDL_QueryTexture(texture,NULL,NULL,w,h);
    TTF_CloseFont(font);

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

void RenderWindow::render(Entity &p_entity,bool jump){

    SDL_Rect src;
    src.x = p_entity.getCurrentFrame().x;
    src.y = p_entity.getCurrentFrame().y;
    src.w = p_entity.getCurrentFrame().w;
    src.h = p_entity.getCurrentFrame().h;

    SDL_Rect dest;
    dest.x = p_entity.getpos().x;
    // if(jump==1)
    //     dest.y = p_entity.getpos().y-120;
    // else
    dest.y = p_entity.getpos().y;
    dest.w = p_entity.getCurrentFrame().w;
    dest.h = p_entity.getCurrentFrame().h;

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


int RenderWindow::random(int low, int high){
    int randNum = low+rand()%(high-low + 1);
    return randNum;
}

void RenderWindow::renderObstacle(Entity &obstacle, bool flagup,int* speed){
    render(obstacle,1);
    obstacle.changepos(*speed,0);
    if(obstacle.getpos().x+obstacle.getCurrentFrame().w<0){
        if(flagup)
            obstacle.setpos(OBSTACLE_POSX,SLIDEOBSTACLEY);

        else
            obstacle.setpos(OBSTACLE_POSX,JUMPOBSTACLEY);
    }
    if(time_passed == threshold){
        --(*speed);
        threshold+=10;
    }
}


void RenderWindow::renderlifeline(Entity &lifeline,bool lifeflag){
    if(lifeflag){
        render(lifeline,2);
        lifeline.changepos(-7,0);
        if(lifeline.getpos().x+lifeline.getCurrentFrame().w<0){
            lifeline.setpos(SCREEN_WIDTH,SCREEN_HEIGHT-150);
        }
    }

}



void RenderWindow::display(){
    SDL_RenderPresent(renderer);
}


void RenderWindow::lives_show(int& life){
    std::string lifestring = "Lives: "+std::__cxx11::to_string(life);

    int text_w,text_h;
    SDL_Texture* texture = Textload(lifestring,"fonts/Antonio-Bold.ttf",50,255,0,0,&text_w,&text_h);
    Entity lifeboard = Entity(Vector2f(1100,50),texture,text_w,text_h,0,0);

    render(lifeboard);
}