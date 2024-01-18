// STL
#include <vector>
#include <string>
#include <memory>

// Classes
#include "GameSession.h"
#include "GameConfig.h"
#include "Rule.h"

class Game {
    public:
        Game();
        ~Game();
        GameConfig* getGameConfig ();
        GameSession* getGameSession();
        std::string getConfigFromFile(std::string );
        // std::string handleMessage(Game::MessageType msgType, int player_id, int value);

        std::vector<std::unique_ptr<Rule>> rules;
    private:
        std::shared_ptr<GameConfig> configurations;
        std::unique_ptr<GameSession> session;

};
