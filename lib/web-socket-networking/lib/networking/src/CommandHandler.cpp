#include "CommandHandler.h"
#include "json.hpp"
#include "Parser.h"
#include <iostream>
#include <fstream>  

CommandHandler::CommandHandler()
{
    
}
CommandHandler::~CommandHandler()
{
}

Command CommandHandler::stringToCommandEnum(std::string command)
{
    //is there a better way to go about doing this?
    if(command == "/addgame") return Command::ADDGAME;
    if(command == "/disconnect") return Command::DISCONNECT;
    if(command == "/connect") return Command::CONNECT;

    return Command::INVALID;
}

void CommandHandler::executeCommand(std::string input)
{
   
    CommandAndArguments caa = processInput(input);

    switch (stringToCommandEnum(caa.command))
    {
    case Command::ADDGAME:
        saveGameFile(caa.allArguments);
        break;
    
    case Command::DISCONNECT:
        //disconnect();
        break;

    case Command::CONNECT:
        //connect();
        break;

    case Command::INVALID:
        //add error message for invalid command
        break;
    default:
        
        break;
    }
}

std::string CommandHandler::formatSaveGameFileName(std::string gameName)
{
    std::string fileSaveLocation = "savedGames/";
    std::string fileExtension = ".json";

    return fileSaveLocation + gameName + fileExtension;

}

void CommandHandler::saveGameFile(std::string stringGameFile)
{
    Parser p = Parser();
    nlohmann::json_abi_v3_11_2::json gameFile = json::parse((stringGameFile));

    std::string gameName = gameFile["configuration"]["name"].get<std::string>();
    
    std::string saveGameFile = formatSaveGameFileName(gameName);

    std::ofstream newGameFile(saveGameFile);

    newGameFile << std::noskipws << stringGameFile << std::endl;

    newGameFile.close();

}

CommandAndArguments CommandHandler::processInput(std::string input){
    std::vector<std::string> result;
    boost::split(result, input,     
    boost::is_any_of(" "));
    CommandAndArguments userCommand;
    userCommand.command = result[0];

    for(uint i = 1; i < result.size(); i++)
    {
        userCommand.arguments.push_back(result[i]);
        userCommand.allArguments +=result[i];
    }
    
    return userCommand;
}