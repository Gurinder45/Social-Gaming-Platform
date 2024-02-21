#pragma once

#include <vector>
#include "../../users/include/users.h"

class GameSession {
public:
    GameSession();
    std::vector<Users> getPlayers();
    std::vector<Users> getAudience();
    int getGame(); //need to return a game object once that is created
private:
    std::vector<Users> playerList;
    std::vector<Users> audienceList;
};
