#include "GameSession.h"

GameSession::GameSession() {
    audienceList = {};
    playerList = {};
}

std::vector<Users> GameSession::getAudience() {
    return audienceList;
}

std::vector<Users> GameSession::getPlayers() {
    return playerList;
}