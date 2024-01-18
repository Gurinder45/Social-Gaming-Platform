#pragma once

#include <GameConfig.h>
#include <string>

class Condition
{
public:
    Condition(std::string condition, GameConfig &config);
    bool evaluate();

    

private:
    std::string condition;
    GameConfig &config;
};
