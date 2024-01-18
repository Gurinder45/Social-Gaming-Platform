// STL
#include <list>
#include <vector>

// BOOST
#include <boost/algorithm/string.hpp>

enum Command
{
    ADDGAME,
    JOIN_GAME,
    LEAVE_GAME,
    DISCONNECT,
    INVALID,
    CREATE_GAME,
    CHANGE_USERNAME,
    CHANGE_ROLE,
    GAME_ID,
    CHAT,
    GAMEINFO,
    STARTGAME,
    LAST_MSG
};

struct CommandAndArguments
{
    std::string command;
    std::vector<std::string> arguments;
    std::string allArguments;
};

class CommandHandler
{

private:
    /* data */
    std::string formatSaveGameFileName(std::string gameName);

public:
    CommandHandler();
    ~CommandHandler();
    CommandAndArguments processInput(std::string input);
    Command stringToCommandEnum(std::string command);
    void saveGameFile(std::string stringGameFile);
    void executeCommand(std::string caa);
};
