#pragma once

#include<iostream>
#include<vector>
#include<algorithm>
#include "RenderWindow.hpp"



enum{
    WELCOME_SCREEN,
    MAIN_MENU,
	NEWGAMEPLAY,
    LOADGAMEPLAY,
	GAMEOVER,
	HIGHSCORE,
	OPTIONS
};

void write_history(int point, int life, int speed, float agent_pos_X, float enemy_pos_X, Entity obstacle1, Entity obstacle2, Entity lifeline){
    FILE *continue_game= fopen("data/history.txt","w");
    fprintf(continue_game,"Score: %d\n",point);
    fprintf(continue_game,"Life: %d\n",life);
    fprintf(continue_game,"Speed: %d\n",speed);
    fprintf(continue_game,"AgentPosX: %f\n",agent_pos_X);
    fprintf(continue_game,"EnemyPosX: %f\n",enemy_pos_X);
    fprintf(continue_game,"Obstacle1PosX: %f\n",obstacle1.getpos().x);
    fprintf(continue_game,"Obstacle1PosY: %f\n",obstacle1.getpos().y);
    fprintf(continue_game,"Obstacle2PosX: %f\n",obstacle2.getpos().x);
    fprintf(continue_game,"Obstacle2PosY: %f\n",obstacle2.getpos().y);
    fprintf(continue_game,"LifeX: %f\n",lifeline.getpos().x);
    fclose(continue_game);
}

void read_history(int* point, int* prev_point, int* life, int* speed, bool* life_present, int game_status){
    char str[100];
    float enemypos, agentpos;
    float obstacle1_pos_X,obstacle2_pos_X,obstacle1_pos_Y,obstacle2_pos_Y,lifeX;
    FILE *continue_game= fopen("data/history.txt","r");

    fscanf(continue_game,"%s",str);
    fscanf(continue_game,"%d",prev_point);

    fscanf(continue_game,"%s",str);
    fscanf(continue_game,"%d",life);

    fscanf(continue_game,"%s",str);
    fscanf(continue_game,"%d",speed);

    fscanf(continue_game,"%s",str);
    fscanf(continue_game,"%f",&agentpos);

    fscanf(continue_game,"%s",str);
    fscanf(continue_game,"%f",&enemypos);
    
    fscanf(continue_game,"%s",str);
    fscanf(continue_game,"%f",&obstacle1_pos_X);

    fscanf(continue_game,"%s",str);
    fscanf(continue_game,"%f",&obstacle1_pos_Y);

    fscanf(continue_game,"%s",str);
    fscanf(continue_game,"%f",&obstacle2_pos_X);

    fscanf(continue_game,"%s",str);
    fscanf(continue_game,"%f",&obstacle2_pos_Y);
    
    fscanf(continue_game,"%s",str);
    fscanf(continue_game,"%f",&lifeX);

    if(lifeline.getpos().x+lifeline.getCurrentFrame().w>=0 && lifeline.getpos().x<SCREEN_WIDTH){
        *life_present=true;
        lifeline.setpos(lifeX,SCREEN_HEIGHT-200);
    }
    else{
        lifeline.setpos(SCREEN_WIDTH,SCREEN_HEIGHT-200);
        *life_present = false;
    }
    
    if(lifeline.getpos().x+lifeline.getCurrentFrame().w>=0 && lifeline.getpos().x<SCREEN_WIDTH){
        *life_present=true;
        lifeline.setpos(lifeX,SCREEN_HEIGHT-200);
    }
    else{
        lifeline.setpos(SCREEN_WIDTH,SCREEN_HEIGHT-200);
        *life_present = false;
    }
    
    if(lifeline.getpos().x+lifeline.getCurrentFrame().w>=0 && lifeline.getpos().x<SCREEN_WIDTH){
        *life_present=true;
        lifeline.setpos(lifeX,SCREEN_HEIGHT-200);
    }
    else{
        lifeline.setpos(SCREEN_WIDTH,SCREEN_HEIGHT-200);
        *life_present = false;
    }
    

    
    if(*life<=0 || (agentpos<=enemypos)||game_status==NEWGAMEPLAY){
        *point=0;
        *prev_point = 0;
        *life = 3;
        *speed=-15;
        agentpos=200;
        enemypos=15;
        obstacle1_pos_X = 1500;
        obstacle1_pos_Y = SLIDEOBSTACLEY;
        obstacle2_pos_X = 2550;
        obstacle2_pos_Y = JUMPOBSTACLEY;
        lifeX = SCREEN_WIDTH;
    }

    if(game_status != 2){
        std::cout<<"change\n";
        int enemy_flag=1,agent_flag=1;

        if(enemypos==15) enemy_flag=0;
        if(agentpos==200) agent_flag=0;


        for (int i = 0; i < (int)running_enemy.size(); i++)
        {
            running_enemy[i].setpos(enemypos+5*i*enemy_flag);
            running_agent[i].setpos(agentpos+5*i*agent_flag);
        }
        for (int i = 0; i < (int)jumping_agent.size(); i++)
        {
            jumping_agent[i].setpos(agentpos+5*i*agent_flag,SCREEN_HEIGHT-210-120);
        }
        for (int i = 0; i < (int)sliding_agent.size(); i++)
        {
            sliding_agent[i].setpos(agentpos+5*i*agent_flag);
        }
    }

    
    obstacle_array[0].setpos(obstacle1_pos_X,obstacle1_pos_Y);
    obstacle_array[1].setpos(obstacle2_pos_X,obstacle2_pos_Y);
    
    fclose(continue_game);
}



void highscorewrite(){
    std::vector<int> scoretable(5);
    FILE *read;

    read = fopen("data/history.txt","r");
    char temp[100];
    int t_score;
    fscanf(read,"%s",temp);
    fscanf(read,"%d",&t_score);
    fclose(read);

    read = fopen("data/highscore.txt","r");
    for (int i = 0; i < (int)scoretable.size(); i++)
    {
        fscanf(read,"%d\n",&scoretable[i]);
    }
    scoretable.push_back(t_score);
    sort(scoretable.rbegin(),scoretable.rend());
    scoretable.pop_back();
    fclose(read);


    
    

    FILE* write = fopen("data/highscore.txt","w");
    for (int i = 0; i < (int)scoretable.size(); i++)
    {
        fprintf(write,"%d\n",scoretable[i]);
    }
    fclose(write);
}

void highscoreshow(){
    FILE* read,*write;
    std::vector<int> scoretable(5);
    read = fopen("data/highscore.txt","r");

    for (int i = 0; i < 5; i++)
    {
        fscanf(read,"%d",&scoretable[i]);
    }
    fseek(read,0,SEEK_SET);
    fclose(read);



    write = fopen("data/highscore.txt","w");
    for (int i = 0; i < 5; i++)
    {
        fprintf(write,"%d\n",scoretable[i]);
    }


    int texty=200;

    for (int i = 0; i < (int)scoretable.size(); i++)
    {   

        std::string serial = std::__cxx11::to_string(i+1)+".";
        std::string scorestring = std::__cxx11::to_string(scoretable[i]);

        int text_w1,text_h1;
        int text_w2,text_h2;
        SDL_Texture* texture = window.Textload(scorestring,"fonts/Antonio-Bold.ttf",75,53,233,137,&text_w1,&text_h1);
        SDL_Texture* texture2 = window.Textload(serial,"fonts/Antonio-Bold.ttf",75,53,233,137,&text_w2,&text_h2);
        Entity scoreboard = Entity(Vector2f(700,texty),texture,text_w1,text_h1,0,0);
        Entity serialno = Entity(Vector2f(500,texty),texture2,text_w2,text_h2,0,0);
        texty+=100;
        window.render(serialno);
        window.render(scoreboard);

    }
    fclose(write);
    
}
