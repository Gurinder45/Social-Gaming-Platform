#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include "json.hpp"
#include <boost/algorithm/string.hpp>

using json = nlohmann::json;


class Parser
{
private:
    std::string jsonString;
public:
    Parser();
    Parser(std::string);
    ~Parser();

    void test();

    std::string parseFile(std::string file);
    nlohmann::json_abi_v3_11_2::json fileToJsonObj(std::string);
    // nlohmann::json_abi_v3_11_2::json stringToJsonObj(std::string); TODO: may not actually need this function
    bool verifyJsonFromFile(std::string fileName);

};
