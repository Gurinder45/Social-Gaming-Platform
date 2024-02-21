#include <iostream>
//#include <boost/lambda/lambda.hpp>

class Users{
    public:
    Users();
    Users(std::string username);
    ~Users() {}

    void changeUsername(std::string username);
    void UserLevelUp();
    void UserSetHost();
    void UserSetSpectator();
    void UserSetPlayer();
    // void UserSetGameSession(GameSession thisSession);

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
    // GameSession GetUserGameSession() {
    //     return gameSession;
    // }
    
    protected:
    std::string userName;
    int userLevel;
    bool isHost;
    bool isSpectator;
    bool isPlayer;
    // GameSession gameSession;
};
