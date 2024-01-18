#pragma once

// STL
#include <vector>

// Classes
#include "users.h"
#include "GameConfig.h"

class GameSession {
public:
    GameSession();

    GameSession(int code);
    GameSession(std::string gameSessionName, std::string gameSessionCode);
    int getInviteCode();
    int generateRandomInviteCode();
    Users getPlayer(networking::Connection &connection);
    void removePlayer(Users user);
    Users getHost(networking::Connection connection);

    std::vector<Users> getPlayers();
    std::vector<Users> getAudience();

    std::string GetGameSessionName();
    std::string GetGameSessionCode();

    void SetGameSessionName(std::string gameSessionName);
    void SetGameSessionCode(std::string gameSessionCode);
    void SetInviteCode(int inviteCode);

    void addPlayer(Users player);
    void addAudience(Users audience);

    int getGame(); //need to return a game object once that is created

private:
    std::vector<Users> playerList;
    std::vector<Users> audienceList;

    std::string gameSessionName;
    std::string gameSessionCode;

    int inviteCode;

};
