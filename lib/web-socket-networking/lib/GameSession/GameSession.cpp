// STL
#include <random>
#include <fstream>

// Classes
#include "GameSession.h"

GameSession::GameSession() {
    this->gameSessionName = "";
    this->gameSessionCode = "";
    audienceList = {};
    playerList = {};
    inviteCode = generateRandomInviteCode();
}

GameSession::GameSession(std::string gameSessionName, std::string gameSessionCode) {
    this->gameSessionName = gameSessionName;
    this->gameSessionCode = gameSessionCode;
    audienceList = {};
    playerList = {};
    inviteCode = generateRandomInviteCode();
    // configurations = std::make_unique<GameConfig>();
    // game = std::make_unique<Game>();
    // std::cout << "Game constructor called" << std::endl;
    // std::cout<< "Constructor invite code: " << inviteCode << std::endl;
}

GameSession::GameSession(int code) {
    audienceList = {};
    playerList = {};
    inviteCode = code;
    // configurations = std::make_unique<GameConfig>();
    // game = std::make_unique<Game>();
    std::cout << "Game constructor called" << std::endl;
    std::cout<< "Constructor invite code: " << inviteCode << std::endl;
}

Users GameSession::getPlayer(networking::Connection &connection) {
    for (auto &player : playerList) {
        if (player.getConnection() == connection) {
            return player;
        }
    }
    ;
}

void GameSession::addPlayer(Users user){
    playerList.push_back(user);
}

void GameSession::removePlayer(Users user){
}

int GameSession::generateRandomInviteCode(){
    std::random_device rd; 
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> distr(0, 9999); 
    return distr(gen);
}
Users GameSession::getHost(networking::Connection connection){
    // for(auto user: playerList){
    //     if(user.getConnection() == connection){
    //         return user;
    //     }
    // }
}

int GameSession::getInviteCode() {
    return inviteCode;
}

std::vector<Users> GameSession::getAudience() {
    return audienceList;
}

std::vector<Users> GameSession::getPlayers() {
    return playerList;
}

std::string GameSession::GetGameSessionName() {
    return gameSessionName;
}

std::string GameSession::GetGameSessionCode() {
    return gameSessionCode;
}

void GameSession::SetGameSessionName(std::string gameSessionName) {
    this->gameSessionName = gameSessionName;
}

void GameSession::SetGameSessionCode(std::string gameSessionCode) {
    this->gameSessionCode = gameSessionCode;
}

void GameSession::SetInviteCode(int inviteCode) {
    this->inviteCode = inviteCode;
}

void GameSession::addAudience(Users audience) {
    audienceList.push_back(audience);
}
