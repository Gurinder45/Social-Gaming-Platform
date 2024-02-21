#include "users.h"
//#include "../GameSession/include/GameSession.h"
//#include <iostream>
//#include <boost/lambda/lambda.hpp>

Users::Users(){
    this->userName = "";
    this->userLevel = 0;
    this->isHost = false;
    this->isSpectator = false;
    this->isPlayer = false;
    std::cout << "Null User Succesfully Created" << std::endl;
}

Users::Users(std::string username){
    this->userName = username;
    this->userLevel = 1;
    this->isHost = false;
    this->isSpectator = false;
    this->isPlayer = false;
    std::cout << "User " << username << " Succesfully Created" << std::endl;
}

void Users::changeUsername(std::string username){
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

// void UserSetGameSession(GameSession thisSession){
//     this->gameSession = thisSession;
// }

void Users::UserRemoveHost(){
    this->isHost = false;
}
void Users::UserRemoveSpectator(){
    this->isSpectator = false;
}

