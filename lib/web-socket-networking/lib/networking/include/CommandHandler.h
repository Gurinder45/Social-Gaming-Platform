#include <list>
#include <vector>
#include <boost/algorithm/string.hpp>


enum Command{
    ADDGAME,
    CONNECT,
    DISCONNECT,
    INVALID 
};


struct CommandAndArguments{
    std::string command;
    std::vector<std::string> arguments;
    std::string allArguments;
};

class CommandHandler
{
private:
    /* data */
    Command stringToCommandEnum(std::string command);
    std::string formatSaveGameFileName(std::string gameName);
public:
    CommandHandler();
    ~CommandHandler();
    CommandAndArguments processInput(std::string input);
    void saveGameFile(std::string stringGameFile);
    void executeCommand(std::string caa);
};
