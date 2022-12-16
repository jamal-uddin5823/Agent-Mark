#pragma once

#include<iostream>
#include "RenderWindow.hpp"


void write_history(int* point, int* life, int* speed, float* enemy_pos_X){
    FILE *continue_game= fopen("data/history.txt","w");
    fprintf(continue_game,"Score: %d\nLife: %d\nSpeed: %d\nEnemyPosX: %lf\n",*point,*life, *speed,*enemy_pos_X);
    fclose(continue_game);
}

void read_history(int* point, int* life, int* speed){
    char str[100];
    float x;
    FILE *continue_game= fopen("data/history.txt","r");

    fscanf(continue_game,"%s",str);
    fscanf(continue_game,"%d",point);
    fscanf(continue_game,"%s",str);
    fscanf(continue_game,"%d",life);
    fscanf(continue_game,"%s",str);
    fscanf(continue_game,"%d",speed);
    fscanf(continue_game,"%s",str);
    fscanf(continue_game,"%f",&x);
    if(*life==0){
        *point = 0;
        *life = 3;
        *speed=-15;
    }
    fclose(continue_game);
}
