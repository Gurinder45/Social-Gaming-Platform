// STL
#include <random>
#include <iostream>
#include <fstream>

// Classes
#include "../networking/include/json.hpp"
#include "Game.h"

// Using
using json = nlohmann::json;

// Helper Functions
bool verifyJsonFile(std::string fileName)
{
    try
    {
        std::ifstream f(fileName);
        json data = json::parse(f);
        return true;
    }
    catch (nlohmann::json_abi_v3_11_2::detail::parse_error &e)
    {
        return false;
    }
}

bool stringToBool(std::string str)
{
    std::istringstream is(str);
    bool b;
    is >> std::boolalpha >> b;
    return b;
}

// Game Implementation
Game::Game()
{
    configurations = std::make_unique<GameConfig>();
    session = std::make_unique<GameSession>();
}

Game::~Game()
{
}

GameConfig *Game::getGameConfig()
{
    return configurations.get();
}

GameSession *Game::getGameSession()
{
    return session.get();
}

std::string Game::getConfigFromFile(std::string fileName)
{
    if (verifyJsonFile(fileName))
    {
        std::ifstream f(fileName);
        json data = json::parse(f);
        configurations->setName(data["configuration"]["name"]);
        configurations->setPlayerCount(data["configuration"]["player count"]["min"], data["configuration"]["player count"]["max"]);
        configurations->setAudience(data["configuration"]["audience"]);

        // parse the setup
        VarPool setup;
        setup.addJson(data["configuration"]["setup"]);
        configurations->addVar("setup", setup);

        // add the constants and variables to game Configaration's varpool
        configurations->addJson(data["constants"]);
        configurations->addJson(data["variables"]);

        /** @TODO: Will need to be able to go through every rule in the JSON here.
         * Currently, this is code that only receives a Global Message rule.
         */
        auto dataRules = data["rules"];
        rules.push_back(std::move(parseRules(dataRules, *configurations, *session)));

        // for (auto &rule : dataRules)
        // {
        //     rules.push_back(parseRules(rule, configurations));
        // }

        f.close();
        return "Success";
    }
    else
    {
        return "Failure";
    }
}
