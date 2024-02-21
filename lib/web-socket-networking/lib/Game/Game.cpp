#include "Game.h"
#include <random>
#include <iostream>
#include <fstream>
#include "../networking/include/json.hpp"
using json = nlohmann::json;
Game::Game() {
    inviteCode = generateRandomInviteCode();
    configurations = std::make_unique<GameConfig>();
    session = std::make_unique<GameSession>();
    std::cout << "Game constructor called" << std::endl;
    std::cout<< "Constructor invite code: " << inviteCode << std::endl;
}

Game::~Game() {

}
int Game::getInviteCode() {
    return inviteCode;
}

int Game::generateRandomInviteCode(){
    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> distr(0, 9999); 
    return distr(gen);
}

int Game::addPlayer() {
    if (session->getPlayers().size() < configurations->getMaxPlayerCount()) {
        //insert user
    }
    return 0;
}

int Game::addAudience() {
    return 0;
}

GameConfig* Game::getGameConfig(){
    return configurations.get();
}

bool verifyJsonFile(std::string fileName)
{
    try
    {
        std::ifstream f(fileName);
        json data = json::parse(f);
        return true; 
    }
    catch (nlohmann::json_abi_v3_11_2::detail::parse_error &e)
    {
        return false;
    }
}

bool stringToBool (std::string str){
    std::istringstream is (str);
    bool b;
    is>>std::boolalpha>>b;
    return b;
}

//Call this function after creating a game object 
//to retrieve game configurations from saved Json file.
std::string Game::getConfigFromFile(std::string fileName){
    if(verifyJsonFile(fileName)){
        std::ifstream f(fileName);
        json data = json::parse(f);
        configurations->setName(data["configuration"]["name"]);
        configurations->setPlayerCount(data["configuration"]["player count"]["min"], data["configuration"]["player count"]["max"]);
        configurations->setAudience(data["configuration"]["audience"]);

        //parse the setup
        VarPool setup;
        setup.addJson(data["configuration"]["setup"]);
        configurations->addVar("setup", setup);

        //add the constants and variables to game Configaration's varpool
        configurations->addJson(data["constants"]);
        configurations->addJson(data["variables"]);
        
        for(auto& rule : data["rules"]){
            rules.push_back(parseRules(rule,configurations));
        }

        f.close();
        return "Success";
    }
    else{
        return "Failure";
    }
}

