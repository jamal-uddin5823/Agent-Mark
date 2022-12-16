#pragma once

#include<iostream>
#include "RenderWindow.hpp"


void write_history(){
    FILE *continue_game= fopen("data/history.txt","w");
    fprintf(continue_game,"Score: %d\nLife: %d\nSpeed: %d\n",score,life, OBSTACLE_SPEED);
    fclose(continue_game);
}

void read_history(){
    FILE *continue_game= fopen("data/history.txt","r");
    fscanf(continue_game,"%d %d %d",&score,&life, &OBSTACLE_SPEED);
    if(life==0){
        score=0;
        life = 3;
        OBSTACLE_SPEED=-15;
    }
    fclose(continue_game);
}
