#include "GameConfig.h"
#include <iostream>

GameConfig::GameConfig(){
    name = "";
    audience = false;
    PlayerCount.min = 0;
    PlayerCount.max = 0;
}

std::string GameConfig::getName(){
    return name;
}

bool GameConfig::audienceAllowed(){
    return audience;
}

int GameConfig::getMinPlayerCount(){
    return PlayerCount.min;
}

int GameConfig::getMaxPlayerCount(){
    return PlayerCount.max;
}

void GameConfig::setName(std::string name){
    this->name = name;
}

void GameConfig::setAudience(bool audience){
    this->audience = audience;
}

void GameConfig::setPlayerCount(int min, int max){
    PlayerCount.min = min;
    PlayerCount.max = max;
}
