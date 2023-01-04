#pragma once

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_timer.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_mixer.h>

#include<iostream>
#include<string>


#include "Sprites.hpp"
#include "Music.hpp"
#include "Fileio.hpp"
// #include "Mouse.hpp"
#include "Entity.hpp"

#define NEW_GAME false
#define CONTINUE_PREV_GAME true
#define first_page_change 90



enum Buttons{
    BUTTONX,
    NEW_GAMEBUTTONY,
    LOAD_GAMEBUTTONY,
    HIGHSCOREBUTTONY,
    OPTIONSBUTTONY,
    EXITBUTTONY,
    TOTAL_BUTTONS
};

int button_arr[TOTAL_BUTTONS] = {840,107,255,403,556,701};



extern int game_status;
int game_status=WELCOME_SCREEN;



int first_page_time = 0; //counter to count time spent on startscreen

extern int life;
extern int score;
int life = 3;
int score=0;


int add=0;
const int VEL_X=20;
double ENEMY_VEL=0.25;
int agent_frame_no = 0,enemy_frame_no=0;
bool paused_flag=false;
bool obsflag=0,lifeflag=0;
bool coinflag=0, freerunflag=0;
int agent_frame_select_flag=0;
int initial_score = 0;
bool first_loop = false;
bool life_present_prev = false;
bool coin_present_prev= false;
bool freerun_present_prev=false;
int noDamage=-1;
int prev_paused=0, prev_not_paused=0;
std::pair<int,int> movement;
bool showing=false; 
bool prev_calced=true;
int score_temp=0;
int extra=0;
int prev_score=0;
int freeruntime=0;
int help=0;

bool collideObstacle=false;
bool collideEnemy=false;
bool collideCoin=false;
bool collideLifeline=false;
bool collideFreerun=false;

extern int time_passed;
int extra_time = 0;

int one_game_time = 0;

bool gameStarted = false;

Entity curr_agent_frame = running_agent[agent_frame_no/running_agent.size()];
Entity curr_enemy_frame = running_enemy[enemy_frame_no/running_enemy.size()];


void init_score_life();
void background_scroll();
void select_agent_frame();
void render_agent();
void render_enemy();
void render_obstacle();
void update_agent_pos();
void render_ground();
void reset_frame_no();
void collision_checker(bool& gameRunning);
void render_lifeline();
void render_coin();
void render_freerun();
int generate_score();



void init_score_life(int& game_status){
    if(game_status==LOADGAMEPLAY){
        read_history(&score,&prev_score,&life,&OBSTACLE_SPEED,&life_present_prev,&game_status);
        if(life<=0){
            prev_score=0;
            score=0;
            initial_score=0;
            life = 3;
            OBSTACLE_SPEED=-15;
            obstacle_array[0].setpos(1500,600);
            obstacle_array[1].setpos(2250,600);
        }
    }
    else if(game_status==NEWGAMEPLAY){        
        help=(int)(SDL_GetTicks()/1000)-4;
        score=0;
        initial_score=(-1)*((int)(SDL_GetTicks()/1000));
        life = 3;
        OBSTACLE_SPEED=-15;
        obstacle_array[0].setpos(1500,600);
        obstacle_array[1].setpos(2250,600);
        
    }
}



void background_scroll(){
    static int scrollingOffset = 0;
    if(!paused_flag)scrollingOffset-=5;

    if(scrollingOffset< -background.getCurrentFrame().w)
        scrollingOffset = 0;

    window.renderBG(scrollingOffset,0,background);
    window.renderBG(scrollingOffset+background.getCurrentFrame().w,0,background);
}


void select_agent_frame(){
    if(agent_frame_select_flag==0)
            curr_agent_frame = running_agent[agent_frame_no/running_agent.size()];
    else if(agent_frame_select_flag==1){
        curr_agent_frame = jumping_agent[agent_frame_no/jumping_agent.size()];
        Mix_PlayChannel(-1,jump,0);
    }
    else{
        curr_agent_frame = sliding_agent[agent_frame_no/sliding_agent.size()];
        Mix_PlayChannel(-1,slide,0);
    }
    curr_enemy_frame = running_enemy[enemy_frame_no/running_enemy.size()];

}


void render_countdown_agent(){
    Entity count_agent_frame=curr_agent_frame;
    if(game_status==NEWGAMEPLAY){
        for (int i = 0; i < (int)running_agent.size(); i++)
        {
            running_agent[i].setpos(200+i*5,SCREEN_HEIGHT-210);
        }
        for (int i = 0; i < (int)jumping_agent.size(); i++)
        {
            jumping_agent[i].setpos(200+i*5,SCREEN_HEIGHT-210-120);
        }
        for (int i = 0; i < (int)sliding_agent.size(); i++)
        {
            sliding_agent[i].setpos(200+i*5,SCREEN_HEIGHT-210);
        }
        
        count_agent_frame = running_agent[0];
    }
    window.render(count_agent_frame);
}

void render_countdown_enemy(){
    Entity count_enemy_frame=curr_enemy_frame;
    if(game_status==NEWGAMEPLAY){
        for (int i = 0; i < (int)running_enemy.size(); i++)
        {
            running_enemy[i].setpos(15+i*5,SCREEN_HEIGHT-210);
        }
        count_enemy_frame = running_enemy[0];
    }
    window.render(count_enemy_frame);
}

void render_agent(){
    
    if(agent_frame_select_flag==0|| agent_frame_select_flag==-1)
        window.render(curr_agent_frame);
    else if(agent_frame_select_flag==1)
        window.render(curr_agent_frame,1);
}

void render_enemy(){
    window.render(curr_enemy_frame);
}


void render_obstacle(){
    for(int i=0;i<(int)obstacle_array.size();i++){

        if((int)SDL_GetTicks()<noDamage)
        {
            int current_pos=obstacle_array[i].getpos().x;
            obstacle_array[i].changepos(current_pos-500,0);
            continue;
        }


        if(i!=0 && abs((obstacle_array[i].getpos().x-obstacle_array[i-1].getpos().x))<60)
        {
            int fir=obstacle_array[i].getpos().x;
            int sec=obstacle_array[i-1].getpos().x;
            if(fir>sec)obstacle_array[i].changepos(sec+100, 0);
            else obstacle_array[i-1].changepos(fir+100, 0);
        }
        else if(i==0 && abs((obstacle_array[0].getpos().x-obstacle_array[obstacle_array.size()-1].getpos().x))<60)
        {
            int fir=obstacle_array[obstacle_array.size()-1].getpos().x;
            int sec=obstacle_array[0].getpos().x;
            if(fir<sec)obstacle_array[i].changepos(fir+60, 0);
            else obstacle_array[obstacle_array.size()-1].changepos(sec+60, 0);
        }
        if(!paused_flag){
            if(abs(obstacle_array[0].getpos().x-obstacle_array[1].getpos().x-obstacle_array[1].getCurrentFrame().w)<100){
                obstacle_array[1].changepos(500,0);
                // obstacle_array[1].setpos(-100,600);
            }
        }
        window.renderObstacle(obstacle_array[i],obsflag,&OBSTACLE_SPEED);
            int coin = window.random(1,100);
            
            if(coin>50)
                obsflag=!obsflag;
    }
}

void update_agent_pos(){

    if(!paused_flag){

        for (int i = 0; i < (int)running_agent.size(); i++)
        {
            running_agent[i].changepos(movement.first,movement.second);
        }
        for (int i = 0; i < (int)jumping_agent.size(); i++)
        {
            jumping_agent[i].changepos(movement.first,movement.second);
        }
        for (int i = 0; i < (int)sliding_agent.size(); i++)
        {
            sliding_agent[i].changepos(movement.first,movement.second);
        }
    }
}

void render_ground(){
    int blackBox_x=0,blackBox_y = SCREEN_HEIGHT-96;
    for (int i = 0; i < 40; i++)
    {
        Entity newgrass = Entity(Vector2f(blackBox_x,blackBox_y),blackBoxTexture,96,96,0,0);
        window.render(newgrass);
        blackBox_x+=32;
    }
}

void reset_frame_no(){
    if(agent_frame_no/running_agent.size()>=running_agent.size() && agent_frame_select_flag==0){
            agent_frame_no=0;
    }
    if(agent_frame_no/jumping_agent.size()>=jumping_agent.size() && agent_frame_select_flag==1){
        agent_frame_no=0;
        agent_frame_select_flag=0;
    }
    if(agent_frame_no/sliding_agent.size()>=sliding_agent.size() && agent_frame_select_flag==-1){
        agent_frame_no=0;
        agent_frame_select_flag=0;
    }
    if(enemy_frame_no/running_enemy.size()>=running_enemy.size()){
        enemy_frame_no=0;
        // ENEMY_VEL+=0.1;
    }
}

void collision_checker(bool& gameRunning){
    for(int i=0;i<(int)obstacle_array.size();i++){
        collideObstacle=curr_agent_frame.checkCollision(curr_agent_frame,obstacle_array[i],agent_frame_select_flag);
        collideEnemy=curr_agent_frame.checkCollision(curr_agent_frame,curr_enemy_frame,agent_frame_select_flag);
        collideLifeline = curr_agent_frame.checkCollision(curr_agent_frame,lifeline,agent_frame_select_flag);
        collideCoin = curr_agent_frame.checkCollision(curr_agent_frame,coin,agent_frame_select_flag);
        if(!collideFreerun)
            collideFreerun = curr_agent_frame.checkCollision(curr_agent_frame,freerun,agent_frame_select_flag);


        if((collideObstacle==true ||collideEnemy==true) && noDamage<(int)(SDL_GetTicks())){
            Mix_PlayChannel(-1,collision,0);
            if(collideEnemy==true){
                life=0;
                score=0;
                Mix_PlayChannel(-1,death,0);
                write_history(score,life,OBSTACLE_SPEED,running_agent[enemy_frame_no/running_agent.size()].getpos().x,running_enemy[enemy_frame_no/running_enemy.size()].getpos().x,obstacle_array[0],obstacle_array[1],lifeline);

                highscorewrite();
                SDL_Delay(1000);
                game_status=GAMEOVER;
                // gameRunning=false;
                return;
            }
            if(collideObstacle==true){
                obstacle_array[i].getpos().x=-100;
                life--;
                //printf("%d ", life);
            }
            if(life<=0){
                Mix_PlayChannel(-1,death,0);
                life =0,score=0;
                write_history(score,life,OBSTACLE_SPEED,running_agent[enemy_frame_no/running_agent.size()].getpos().x,running_enemy[enemy_frame_no/running_enemy.size()].getpos().x,obstacle_array[0],obstacle_array[1],lifeline);

                highscorewrite();
                SDL_Delay(1000);
                game_status=GAMEOVER;
            }
            collideObstacle=false;
            collideEnemy=false;

            for (int i = 0; i < (int)running_enemy.size(); i++)
            {
                running_enemy[i].changepos(50,0);
            }
        }

        if(collideLifeline==true){
            Mix_PlayChannel(-1,lifeup,0);
            life++;
            lifeline.getpos().x=-100;
        }

        if(collideCoin==true){
            Mix_PlayChannel(-1,lifeup,0);
            extra-=10;
            coin.getpos().x=-100;
        }

        if(collideFreerun==true){
            if(freeruntime<300)
            {
                std::string s="FREE RUN!";
                int text_w,text_h;
                SDL_Texture* texture = window.Textload(s,"fonts/Antonio-Bold.ttf",50,255,0,0,&text_w,&text_h);
                Entity message = Entity(Vector2f(450,5),texture,text_w,text_h,0,0);
                window.render(message);
                freeruntime++;
                collideFreerun=true;
            }
            else{
                freeruntime=0;
                collideFreerun=false;
            }
            


            Mix_PlayChannel(-1,lifeup,0);
            noDamage=(int)(SDL_GetTicks())+5000;
            freerun.getpos().x=-100;
            }
    }
}


void render_lifeline(){
    int lifecoin = window.random(1,5000);
    if(lifecoin>4995 && !showing){
        lifeflag=1;
        showing=true;
    }
    if(lifeflag||life_present_prev){
        window.render(lifeline);
        if(!paused_flag)lifeline.changepos(-5,0);
        if(lifeline.getpos().x+lifeline.getCurrentFrame().w<0){
            lifeline.setpos(SCREEN_WIDTH,SCREEN_HEIGHT-200);
            lifeflag=false;
            showing=false;
        }
        life_present_prev=false;
    }
}

void render_coin(){
    int coincoin = window.random(1,500);
    if(coincoin>495 && !showing){
        coinflag=1;
        showing=true;
    }
    if(coinflag||coin_present_prev){
        window.render(coin);
        if(!paused_flag)coin.changepos(-5,0);
        if(coin.getpos().x+coin.getCurrentFrame().w<0){
            coin.setpos(SCREEN_WIDTH,SCREEN_HEIGHT-200);
            coinflag=false;
            showing=false;
        }
        coin_present_prev=false;
    }
}

void render_freerun(){
    int freeruncoin = window.random(1,5000);
    if(freeruncoin>4995 && !showing){
        freerunflag=1;
        showing=true;
    }
    if(freerunflag||freerun_present_prev){

        window.render(freerun);
        if(!paused_flag)freerun.changepos(-5,0);
        if(freerun.getpos().x+freerun.getCurrentFrame().w<0){
            freerun.setpos(SCREEN_WIDTH,SCREEN_HEIGHT-200);
            freerunflag=false;
            showing= false;
        }
        freerun_present_prev=false;
    }
}



int generate_score(){
    ////std::cout<<score<<" "<<life<<" "<<initial_score<<'\n';
    //printf("%d ",prev_score);
    if(paused_flag)
    {
        prev_calced=false;
        prev_not_paused=(int)SDL_GetTicks();
        int time=0;
        window.score_show(time,initial_score);
        return initial_score;
    }
    int time = (int)(SDL_GetTicks()/1000);
    if(prev_calced)prev_paused=(int)(SDL_GetTicks()/1000);
    time-=extra_time+5;
    time_passed= time;
    if((time_passed%10==0 && time_passed!=0) && paused_flag==false){
        Mix_PlayChannel(-1,levelup,0);
    }
    initial_score=time-extra+prev_score-help;
    ////std::cout<<"initial score = "<<initial_score<<'\n';
    if(!prev_calced)
    {
        prev_not_paused=int(SDL_GetTicks()/1000);
        //printf("%d %d ",prev_not_paused,prev_paused);
        initial_score-=(prev_not_paused-prev_paused);
        extra+=prev_not_paused-prev_paused;
        //printf("%d\n",initial_score);
        prev_calced=true;
        time=0;
        window.score_show(time ,initial_score);
        return initial_score+time;

    }
    time=0;
    window.score_show(time ,initial_score);
    return initial_score+time;
}