#include "users.h"
#include <boost/lambda/lambda.hpp>
#include <iostream>


Users::Users(){
    this->userName = "";
    this->userLevel = 0;
    this->isHost = false;
    this->isSpectator = false;
    this->isPlayer = false;
    std::cout << "Null User Succesfully Created" << std::endl;
    std::cout << "/-------------------------------------------/" << std::endl;
}

Users::Users(std::string username){
    this->userName = username;
    this->userLevel = 1;
    this->isHost = false;
    this->isSpectator = false;
    this->isPlayer = false;
    std::cout << "User " << username << " Succesfully Created" << std::endl;
    std::cout << "/-------------------------------------------/" << std::endl;
}
Users::Users(networking::Connection c){
    this->userName = "user" + std::to_string(c.id);
    this->userLevel = 1;
    this->isHost = false;
    this->isSpectator = false;
    this->isPlayer = false;
    this->connection = c;
    std::cout << "User " << userName << " Succesfully Created" << std::endl;
    std::cout << "/-------------------------------------------/" << std::endl;
}
networking::Connection Users::getConnection(){
    return this->connection;
}
void Users::changeUsername(std::string_view username){
    this->userName = username;
    std::cout << "Username Succesfully Changed To: " << userName << std::endl;
}

void Users::UserLevelUp(){
    this->userLevel += 1;
}

void Users::UserSetHost(){
    this->isHost = true;
}

void Users::UserSetSpectator(){
    this->isSpectator = true;
}

void Users::UserSetPlayer(){
    this->isPlayer = true;
}

void Users::UserSetGameSessionName(std::string thisSessionName){
    this->gameSessionName = thisSessionName;
}

void Users::UserRemoveHost(){
    this->isHost = false;
}
void Users::UserRemoveSpectator(){
    this->isSpectator = false;
}

