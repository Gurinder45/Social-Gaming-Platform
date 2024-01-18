#include "../../networking/include/json.hpp"
#include "../../GameConfig/include/GameConfig.h"
#include <variant>
#include <map>
#include "boost/variant.hpp"
#include <iostream>
#include <optional>

/*
    GameVariant is used to store data retrieved from the json file. Ideally, this should be placed in a separate class for refactoring
*/
typedef boost::make_recursive_variant<
    int,
    float, 
    bool,
    std::string,
    std::vector<boost::recursive_variant_>,
    std::map<std::string, boost::recursive_variant_>
    >::type GameVariant;

/*
    Visitor to insert a GameVariant into a container. insertPackage has a 'key' field to store the key of the object since boost does not support
    more than 2 arguments within the visitor() function.

    Only implementations for maps (json objects) and vectors are present. Other primitive values have no implementation.
*/
struct insertPackage: public boost::static_visitor<> {
    void operator()(std::map<std::string, GameVariant>&map, const GameVariant& val) const { 
        map.insert({key, val});
    }
    void operator()(std::vector<GameVariant>&list , const GameVariant& val) const { 
        list.push_back(val);
    }
    void operator()(const int map, const auto& val) const { 

    }
    void operator()(const float map, const auto& val) const { 

    }
    void operator()(const  bool map, const auto& val) const { 
       
    }
    void operator()(const std::string map, const auto& val) const { 
       
    }
    std::string key;
};


/*
    Visitor to retrieve the string representation of the value(s) within a GameVariant. 
*/
struct getStringPackage : public boost::static_visitor<std::string> {
    std::string operator()(std::string strVal) const { 
        return strVal;
    }
    std::string operator()(int intVal) const { 
        return std::to_string(intVal); 
    }
    std::string operator()(float floatVal) const {
        return std::to_string(floatVal);
    }
    std::string operator()(bool boolVal) const {
        return boolVal? "true" : "false";
    }
    std::string operator()(std::map<std::string, GameVariant> map) const {
        std::string str;
        str.append("{");
        for (auto it = map.begin(); it != map.end(); it++) {
            str.append(it->first);
            str.append(": ");
            str.append(boost::apply_visitor(getStringPackage{}, it->second));
            str.append(", ");
        }
        if (!str.empty()) {
            str.pop_back();
            str.pop_back();
        }
        str.append("}");
        return str;
    }
    std::string operator()(std::vector<GameVariant> list) const {
        std::string str{"["};
        auto it = list.begin();
        for (;it != list.end()-1; ++it) {
             str.append(boost::apply_visitor(getStringPackage{}, *it));
             str.append(",");
        }
        str.append(boost::apply_visitor(getStringPackage{}, *it));
        str.append("]");
        return str;
    }
};

/*
    Visitor to retrieve the string representation of a value(s) within a map, given the key. 
*/
struct getValueFromKey: public boost::static_visitor<std::optional<std::string>> {
    std::optional<std::string> operator()(std::map<std::string, GameVariant>&map) const {
        auto it = map.find(key);
        if (it != map.end()) {
            return std::optional<std::string>{boost::apply_visitor(getStringPackage{}, it->second)};
        } 
        return std::nullopt;
    }
    std::optional<std::string> operator()(std::vector<GameVariant>&list) const { 
        return std::nullopt;
    }
    std::optional<std::string> operator()(const int intValue) const { 
        return std::nullopt;
    }
    std::optional<std::string> operator()(const float floatValue) const {    
        return std::nullopt;
    }
        
    std::optional<std::string> operator()(const bool boolValue) const { 
       return std::nullopt;
    }
    std::optional<std::string> operator()(const std::string stringValue) const { 
        return std::nullopt;
    }
    std::string key;
};


/*
    Visitor that works on a list of objects. For each object, retrieve the value that is mapped by the key.
    TODO: work on lists that contain other lists.
*/
struct getListPackage: public boost::static_visitor<std::vector<GameVariant>> {
    std::vector<GameVariant> operator()(std::map<std::string, GameVariant>&map) const {
        return std::vector<GameVariant>{};
    }
    std::vector<GameVariant> operator()(std::vector<GameVariant>&list) const { 
        std::vector<GameVariant> values{};
        getValueFromKey pckg;
        for (GameVariant&it: list) {
            switch(it.which()) {
                case 5:
                {
                    pckg.key = key;
                    std::optional<std::string> s = boost::apply_visitor(pckg, it);
                    if (s) {
                        values.push_back(*s);
                    }
                }
                default:
                    break;
            }
        }     
        return values;
    }
    std::vector<GameVariant> operator()(const int intValue) const { 
        return std::vector<GameVariant>{};
    }
    std::vector<GameVariant> operator()(const float floatValue) const { 
        return std::vector<GameVariant>{};
    }
    std::vector<GameVariant> operator()(const bool boolValue) const { 
        return std::vector<GameVariant>{};
    }
    std::vector<GameVariant> operator()(const std::string stringValue) const { 
        return std::vector<GameVariant>{};
    }
    std::string key;
};


class GameParser {
    public:     
        enum MapType {
            CONSTANTS,
            VARIABLES
        };   
        enum GameOptions{
            ROCK_PAPER_SCISSORS,
            TRIVIA,
            WHIPLASH,
            INVALID_OPTION 
        };
        enum ParseResult{
            PARSE_SUCCESS,
            PARSE_FAIL
        };
        struct PlayerCount{
            int minPlayers;
            int maxPlayers;
        }; 
        struct Setup{
            int rounds;
        };
        int getMinPlayers();

        int getMaxPlayers();

        int getRounds();

        bool getAudience();

        std::string getName();
        
        void modifyGamePath(GameOptions options, std::string filePath);

        GameParser::ParseResult parseGameConfigurations(GameOptions option, GameConfig *gameConfig);

        GameParser::ParseResult validateSaveGameConfig(GameParser::GameOptions gameOption);

        std::vector<std::string> nameResolver(std::string);

        std::vector<GameVariant> getList(std::string input);

        std::vector<GameVariant> getListFromList(GameVariant, std::vector<std::string>);

        std::vector<GameVariant> getListFromMap(GameVariant, std::vector<std::string>);
        
    private:
        std::string name;
        PlayerCount playerCount;
        Setup setup;
        bool audience;
        void parseKeys(const nlohmann::json& obj, MapType);
        void initializeMap(GameVariant&map, const nlohmann::json& mapValue);
        void initializeList(GameVariant&list, const nlohmann::json& listValue);
        void addToMap(std::pair<std::string, GameVariant>, MapType);
        std::map<std::string, GameVariant> constants;
        std::map<std::string, GameVariant> variables;
        std::map<std::string, GameVariant> perPlayer;
        std::map<std::string, GameVariant> perAudience;
        std::map<GameOptions, std::string>gameToFileMap{
            {GameOptions::ROCK_PAPER_SCISSORS, "./RockPaperScissors.json"}, 
            {GameOptions::TRIVIA, "./Trivia.json"}, 
            {GameOptions::WHIPLASH, "./Whiplash.json"}};
};
