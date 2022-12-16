#pragma once

#include<iostream>
#include "RenderWindow.hpp"


void write_history(){
    FILE *continue_game= fopen("data/history.txt","w");
    fprintf(continue_game,"%d %d\n",score,life);
    fclose(continue_game);
}

void read_history(){
    FILE *continue_game= fopen("data/history.txt","r");
    fscanf(continue_game,"%d %d",&score,&life);
    fclose(continue_game);
}
