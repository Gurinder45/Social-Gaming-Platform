#include "../../networking/include/json.hpp"
#include "../../GameConfig/include/GameConfig.h"
#include "../../VarPool/include/VarPool.h"
#include "../../Rule/include/Rule.h"
#include <variant>
#include <map>
#include "boost/variant.hpp"
#include <iostream>
#include <string>

// Class to parse rules from JSON file
// Example of JSON file:
// "rules": [
// {
//   "rule": "global-message",
//   "value": "This .json showcases some of the rules we have implemented."
// },
// {
//   "rule": "global-message",
//   "value": "Some of these rules don't actively print to the screen..."
// },
// {
//   "rule": "global-message",
//   "value": "You can check out the rules we have managed to implement inside of /src/GameSpec/..."
// },
// {
//   "rule": "global-message",
//   "value": "This is a score rule that prints out the value for each user"
// },
// {
//   "rule": "scores",
//   "score": "wins",
//   "ascending": "false"
// },
// ]

// This class will parse the rules from the JSON file, and use the VarPool class to store the variables in a map
// The VarPool class will then be used to retrieve the variables when needed
class RuleParser : public VarPool{
    public:
        enum ParseResult{
            PARSE_SUCCESS,
            PARSE_FAIL
        };

        RuleParser();
        ParseResult parseRules(const nlohmann::json& rules);

        ParseResult parseRulestoVarpool(std::string fileName);

        bool verifyJson(std::string fileName);

};











