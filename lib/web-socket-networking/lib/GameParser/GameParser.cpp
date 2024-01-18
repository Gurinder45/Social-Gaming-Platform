#include "GameParser.h"
#include <fstream>
#include <boost/algorithm/string.hpp>
using json = nlohmann::json;


GameParser::ParseResult GameParser::parseGameConfigurations(GameParser::GameOptions gameOption, GameConfig * gameConfig) {

    if(validateSaveGameConfig(gameOption) == GameParser::ParseResult::PARSE_SUCCESS) {
        gameConfig->setName(this->name);
        gameConfig->setPlayerCount(this->playerCount.minPlayers, this->playerCount.maxPlayers);
        gameConfig->setAudience(this->audience);
        return GameParser::ParseResult::PARSE_SUCCESS;
    }
    else{
        return GameParser::ParseResult::PARSE_FAIL;
    }
}

void GameParser::initializeMap(GameVariant&map, const nlohmann::json& mapValue) {
    map = std::map<std::string, GameVariant>{};
    insertPackage insert;
    for (auto& item: mapValue.items()) {
        insert.key = item.key();
        if (item.value().is_string()) {
            GameVariant val = to_string(item.value());
            boost::apply_visitor(insert,map,val);
        }
        if (item.value().is_number_integer()) {
            GameVariant val = item.value().get<int>();
            boost::apply_visitor(insert, map, val);
        }
        else if (item.value().is_number_float()) {
            GameVariant val = item.value().get<float>();
            boost::apply_visitor(insert, map, val);
        }
        else if (item.value().is_boolean()) {
            GameVariant val = item.value().get<bool>();
            boost::apply_visitor(insert, map, val);
        }
        else if (item.value().is_array()) {
            GameVariant list;
            initializeList(list, item.value());
            boost::apply_visitor(insert, map, list);
        }
    }
}
void GameParser::initializeList(GameVariant&list, const nlohmann::json& listValue) {
    list = std::vector<GameVariant>{};
    insertPackage insert;
    for (auto& item: listValue.items()) {
        insert.key = item.key();
        if (item.value().is_string()) {
            GameVariant val = to_string(item.value());
            boost::apply_visitor(insert,list,val);
        }
        if (item.value().is_number_integer()) {
            GameVariant val = item.value().get<int>();
            boost::apply_visitor(insert, list, val);
        }
        else if (item.value().is_number_float()) {
            GameVariant val = item.value().get<float>();
            boost::apply_visitor(insert, list, val);
        }
        else if (item.value().is_boolean()) {
            GameVariant val = item.value().get<bool>();
            boost::apply_visitor(insert, list, val);
        }
        else if (item.value().is_object()) {
            GameVariant map;
            initializeMap(map, item.value());
            boost::apply_visitor(insert, list, map);
        }
    }
}

GameParser::ParseResult GameParser::validateSaveGameConfig(GameParser::GameOptions gameOption)
{
    try
    {
        auto fileToRead = gameToFileMap.find(gameOption);
        if (fileToRead == gameToFileMap.end()) {
            std::cout << "Couldnt find game option" << std::endl;
            return GameParser::ParseResult::PARSE_FAIL;
        }
        std::string input = fileToRead->second;
        std::ifstream inputFile(input);
        json data = json::parse(inputFile);
        /*
            Game configuration object inside the json file will always contain the same variables, so it is okay to index them by keys.
        */
        name = data["configuration"]["name"];
        playerCount.minPlayers = data["configuration"]["player count"]["min"];
        playerCount.maxPlayers = data["configuration"]["player count"]["max"];
        audience = data["configuration"]["audience"];
        setup.rounds = data["configuration"]["setup"]["Rounds"];

        // std::cout << "set name, audience, and playercount" << std::endl;

        /*
           Other objects include constants, variables, per-player, per-audience, and rules. These will contain varying numbers of nested elements so we have
           to iterate through them.           
        */
        json constantsObject = data["constants"];
        for (const auto& item : constantsObject.items())
        {
            if (item.value().is_string()) {
                std::string key {item.key()};
                std::string value{item.value()};
                constants.insert({key,value});
            }
            if (item.value().is_number_integer()) {
                std::string key {item.key()};
                int value = item.value().get<int>();
                constants.insert({key, value});
            }
            else if (item.value().is_number_float()) {
                std::string key {item.key()};
                float value = item.value().get<float>();
                constants.insert({key,value});
            }
            else if (item.value().is_boolean()) {
                std::string key {item.key()};
                bool value = item.value().get<bool>();
                constants.insert({key,value});
            }
            else if (item.value().is_object()) {
                std::string key {item.key()};
                GameVariant map;
                initializeMap(map, item.value());
                constants.insert({key, map});
            }
            else if (item.value().is_array()) {
                std::string key {item.key()};
                GameVariant list = std::vector<GameVariant>{};
                initializeList(list, item.value());
                constants.insert({key, list});
            }
        }
        
        /*
            This is used just to iterate through the constants object. Should be refactored into a test later on.
        */
        for (auto it = constants.begin(); it != constants.end(); it++){
            GameVariant var = it->second;
            std::cout << it->first << ": " << boost::apply_visitor(getStringPackage{}, var) << std::endl;
        }
        std::vector<GameVariant> weaponNames = getList("weapons.name");
        std::string options{};
        for (auto&it: weaponNames) {
            options += boost::apply_visitor(getStringPackage{},it);
            options += ',';
        }
        if (!options.empty()) {
            options.pop_back();
        }
        std::cout << options << std::endl;


        return GameParser::ParseResult::PARSE_SUCCESS; 
    }
    catch (nlohmann::json::parse_error& ex)
    {
        return GameParser::ParseResult::PARSE_FAIL;
    }
}

int GameParser::getMinPlayers() {
    return playerCount.minPlayers;
}

int GameParser::getMaxPlayers() {
    return playerCount.maxPlayers;
}

bool GameParser::getAudience() {
    return audience;
}

std::string GameParser::getName() {
    return name;
}

int GameParser::getRounds() {
    return setup.rounds;
}


void GameParser::modifyGamePath(GameOptions options, std::string filePath) {
    gameToFileMap[options] = filePath;
}

std::vector<std::string> GameParser::nameResolver(std::string input) {
    std::vector<std::string>result;
    boost::split(result, input, boost::is_any_of("."));
    return result;
}

std::vector<GameVariant> GameParser::getList(std::string input) {
    std::vector<std::string> args = nameResolver(input);
    std::vector<GameVariant>values{};

    if (args.size() == 0) {
        return std::vector<GameVariant>{};
    } 

    // input string is not empty, try to get root element
    auto mapIter = constants.find(args[0]);
    if (mapIter == constants.end()) {
        std::cout << "couldn't find root element in map" << std::endl;
        return std::vector<GameVariant>{};
    }

    // Note, if there is more than one level, ie. weapons.name, but weapons is just a primitive value, then this will simply return an empty list, indicating an error.
    switch(mapIter->second.which()) {
        case 4:
            std::cout << "returning values from list" << std::endl;
            args.erase(args.begin());
            return getListFromList(mapIter->second, args);
        case 5:
            args.erase(args.begin());
            std::cout << "returning a value from a map" << std::endl;
            return getListFromMap(mapIter->second, args);
        default:
            if (args.size() == 1) {
                std::cout << "returning a primitive value type" << std::endl;
                values.push_back(mapIter->second);
                return values;
            }
            return std::vector<GameVariant>{}; // empty vector means theres an error.
    }
    return values;
}


std::vector<GameVariant> GameParser::getListFromMap(GameVariant map, std::vector<std::string> args) {
    std::vector<GameVariant> list;
    getValueFromKey pckg;
    pckg.key = args[0];
    std::optional<std::string> value = boost::apply_visitor(pckg, map);
    if (value) {
        list.push_back(*value);
    }
    return list;
}   


std::vector<GameVariant> GameParser::getListFromList(GameVariant list, std::vector<std::string> args) {
    std::vector<GameVariant> returnList;
    getListPackage listPackage;
    listPackage.key = args[0];
    return boost::apply_visitor(listPackage, list);
}
