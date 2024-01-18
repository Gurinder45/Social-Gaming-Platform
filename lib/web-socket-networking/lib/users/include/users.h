#include "../../networking/include/Server.h"
#include <boost/lambda/lambda.hpp>
#include <iostream>
#include <string>

class Users{
    public:
    Users();
    Users(std::string username);
    Users(networking::Connection c);
    ~Users() {}

    void changeUsername(std::string_view username);
    void UserLevelUp();
    void UserSetHost();
    void UserSetSpectator();
    networking::Connection getConnection();
    void UserSetPlayer();
    void UserSetGameSessionName(std::string thisSessionName);

    void UserRemoveHost();
    void UserRemoveSpectator();

    std::string GetUsername() {
        return userName;
    }
    int GetUserLevel() {
        return userLevel;
    }
    bool GetUserHostStatus() {
        return isHost;
    }
    bool GetUserSpectatorStatus() {
        return isSpectator;
    }
    bool GetUserPlayerStatus() {
        return isPlayer;
    }
    std::string GetUserGameSessionName() {
        return gameSessionName;
    }
    
    // bool operator==(const Users& user)
    // {
    //     return(userName==user.userName);
    // }

   protected:
    std::string userName;
    int userLevel;
    bool isHost;
    bool isSpectator;
    bool isPlayer;
    std::string gameSessionName;
    networking::Connection connection;
    // GameSession gameSession;

};
