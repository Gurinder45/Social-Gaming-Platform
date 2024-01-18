#include "Parser.h"
Parser::Parser(){

}
Parser::Parser(std::string fileName)
{
    jsonString = parseFile(fileName);
}
Parser::~Parser()
{
}

std::string Parser::parseFile(std::string fileName)
{
    std::ifstream f(fileName);
    if(verifyJsonFromFile(fileName)){
        json data = json::parse(f);
        return data.dump();
    }
    else{
        return "Invalid json file";
    }
}
nlohmann::json_abi_v3_11_2::json Parser::fileToJsonObj(std::string fileName){
    std::ifstream f(fileName);
    if(verifyJsonFromFile(fileName)){
        json data = json::parse(f);
        return data;
    }
    else{
        return NULL;
    }  
}

bool Parser::verifyJsonFromFile(std::string fileName)
{
    try
    {
        std::ifstream f(fileName);
        json data = json::parse(f);
        return true; 
    }
    catch (nlohmann::json_abi_v3_11_2::detail::parse_error e)
    {
        return false;
    }
}