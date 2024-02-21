#include <vector>
#include <string>
#include "../../GameSession/include/GameSession.h"
#include "../../GameConfig/include/GameConfig.h"
#include <memory>
#include "Rule.h"
class Game {
    public:
        Game();
        ~Game();
        int addAudience();
        int addPlayer();
        int getInviteCode();
        int generateRandomInviteCode();
        int removePlayer();
        int removeAudience();
        GameConfig* getGameConfig ();
        std::string getConfigFromFile(std::string );
        // std::string handleMessage(Game::MessageType msgType, int player_id, int value);
    private:
        int inviteCode;
        std::shared_ptr<GameConfig> configurations;
        std::unique_ptr<GameSession> session;

        std::vector<std::unique_ptr<Rule>> rules;
        // value is probably type Message used in provided server code instead of int
};
