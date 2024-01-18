/////////////////////////////////////////////////////////////////////////////
//                         Single Threaded Networking
//
// This file is distributed under the MIT License. See the LICENSE file
// for details.
/////////////////////////////////////////////////////////////////////////////

#include "Server.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>
#include "CommandHandler.h"
#include "ServerHandler.h"

using networking::Connection;
using networking::Message;
using networking::Server;

ServerHandler serverHandler;

void onConnect(Connection c)
{
    std::cout << "New connection found: " << c.id << "\n";
    Users newUser{c};
    serverHandler.addUser(newUser);
}

void onDisconnect(Connection c)
{
    std::cout << "Connection lost: " << c.id << "\n";
    serverHandler.removeClient(c);
}

struct MessageResult
{
    std::string result;
    bool shouldShutdown;
};

std::deque<Message> buildOutgoing(const std::string &log, std::vector<Users> userList)
{
    std::deque<Message> outgoing;
    for (auto user : userList)
    {
        outgoing.push_back({user.getConnection(), log});
    }
    return outgoing;
}

MessageResult processMessages(Server &server, const std::deque<Message> &incoming)
{
    std::ostringstream result;
    bool quit = false;
    CommandHandler commandHandler;

    for (auto &message : incoming)
    {
        std::vector<std::string> words;
        boost::split(words, message.text, boost::is_any_of(" "), boost::token_compress_on);
        switch (commandHandler.stringToCommandEnum(words[0]))
        {
        case Command::DISCONNECT:
        {
            serverHandler.disconnectFromServer(message, server);
            break;
        }
        case Command::CREATE_GAME:
        {
            serverHandler.createGame(message, server);
            break;
        }
        case Command::CHANGE_USERNAME:
        {
            serverHandler.changeUsername(message, server, words[1]);
            break;
        }
        case Command::JOIN_GAME:
        {
            serverHandler.joinGame(message, server, words[1]);
            break;
        }
        case Command::LEAVE_GAME:
        {
            serverHandler.leaveGame(message, server, words[1]);
            break;
        }
        case Command::GAME_ID:
        {
            serverHandler.showGameId(message, server);
            break;
        }
        case Command::CHAT:
        {
            serverHandler.printChatMessage(message, server);
            break;
        }
        case Command::ADDGAME:
        {
            serverHandler.addGame(message);
            break;
        }
        case Command::INVALID:
        {
            serverHandler.invalidCommand();
            break;
        }
        case Command::GAMEINFO:
        {
            serverHandler.showGameInfo(message, server);
            break;
        }
        case Command::STARTGAME:
        {
            serverHandler.startGame(message, server);
        }
        case Command::LAST_MSG:
        {
            serverHandler.getLastMessage(message, server);
        }
        default:
        {
            break;
        }
        }
    }
    return MessageResult{result.str(), quit};
}

std::string getHTTPMessage(const char *htmlLocation)
{
    if (access(htmlLocation, R_OK) != -1)
    {
        std::ifstream infile{htmlLocation};
        return std::string{std::istreambuf_iterator<char>(infile), std::istreambuf_iterator<char>()};
    }
    else
    {
        std::cerr << "Unable to open HTML index file:\n"
                  << htmlLocation << "\n";
        std::exit(-1);
    }
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << "Usage:\n  " << argv[0] << " <port> <html response>\n"
                  << "  e.g. " << argv[0] << " 4002 ./webchat.html\n";
        return 1;
    }

    unsigned short port = std::stoi(argv[1]);
    Server server{port, getHTTPMessage(argv[2]), onConnect, onDisconnect};

    std::cout << "Server started \n";
    std::cout << "/-----------------------------/\n";

    while (true)
    {
        bool errorWhileUpdating = false;
        try
        {
            server.update();
        }
        catch (std::exception &e)
        {
            std::cerr << "Exception from Server update:\n"
                      << " " << e.what() << "\n\n";
            errorWhileUpdating = true;
        }

        auto incoming = server.receive();
        auto [log, shouldQuit] = processMessages(server, incoming);

        if (shouldQuit || errorWhileUpdating)
        {
            break;
        }

        sleep(1);
    }

    return 0;
}
