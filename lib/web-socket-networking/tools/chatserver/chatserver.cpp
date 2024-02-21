/////////////////////////////////////////////////////////////////////////////
//                         Single Threaded Networking
//
// This file is distributed under the MIT License. See the LICENSE file
// for details.
/////////////////////////////////////////////////////////////////////////////

#include "Server.h"

#include "Game.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>
// #include "GameSession.h"
#include "CommandHandler.h"

using networking::Connection;
using networking::Message;
using networking::Server;

std::vector<Connection> clients;
std::vector<std::unique_ptr<GameSession>> sessions;
std::vector<Users> users;

void onConnect(Connection c)
{
    std::cout << "New connection found: " << c.id << "\n";
    Users newUser{c};
    sessions[0]->addPlayer(newUser);
    users.push_back(newUser);
}

void onDisconnect(Connection c)
{
    std::cout << "Connection lost: " << c.id << "\n";
    auto eraseBegin = std::remove(std::begin(clients), std::end(clients), c);
    clients.erase(eraseBegin, std::end(clients));
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
        case Command::DISCONNECT: {
            server.disconnect(message.connection);
            break;
        }
        case Command::CREATE_GAME: {
            std::cout << "Request to create game received from client: " << message.connection.id << std::endl;
            auto newGame = std::make_unique<GameSession>();
            sessions.push_back(std::move(newGame));
            std::cout << "Current number of games: " << sessions.size() << std::endl;
            std::cout << "A new game has been created with invite code: " << sessions.back()->getInviteCode() << std::endl;
            for (auto &session : sessions)
            {
                for (auto player : session->getPlayers())
                {
                    if (player.getConnection().id == message.connection.id)
                    {
                        auto outgoing =
                            buildOutgoing("You created a game with code: " + std::to_string((*session).getInviteCode()),
                                          std::vector<Users>{player});
                        server.send(outgoing);
                    }
                }
            }
            break;
        }
        case Command::CHANGE_USERNAME: {
            auto user = std::find_if(begin(users), end(users),
                                     [message](Users &user) { return user.getConnection() == message.connection; });
            if (user != users.end())
            {
                user->changeUsername(words[1]);
                std::cout << "Succesfully changed username for " << message.connection.id << " to "
                          << user->GetUsername() << std::endl;
                for (auto &session : sessions)
                {
                    for (auto player : (*session).getPlayers())
                    {
                        if (player.getConnection().id == message.connection.id)
                        {

                            auto outgoing = buildOutgoing("You have changed your username to " + player.GetUsername(),
                                                          std::vector<Users>{player});
                            server.send(outgoing);
                        }
                    }
                }
            }
            else
            {
                std::cout << "Couldn't find a connection somehow..." << std::endl;
            }
            break;
        }
        case Command::JOIN_GAME: {
            auto requestedSession = std::find_if(begin(sessions), end(sessions), [words](std::unique_ptr<GameSession> &session) {
                return session->getInviteCode() == stoi(words[1]);
            });
            if (requestedSession != sessions.end())
            {
                std::cout << "user has requested to join a game that is available!" << std::endl;
                auto user = std::find_if(begin(users), end(users),
                                         [message](Users &user) { return user.getConnection() == message.connection; });
                if (user != users.end())
                {
                    (*requestedSession)->addPlayer(*user);
                }
                std::string userid = (*user).GetUsername() + " has joined the game\n";

                auto outgoing = buildOutgoing(userid, (*requestedSession)->getPlayers());
                server.send(outgoing);
                break;
            }
            else
            {
                std::cout << "user provided invalid invite code" << std::endl;
            }
            break;
        }
        case Command::LEAVE_GAME: {
            // auto requestedGame = std::find_if(begin(sessions), end(sessions), [words](std::unique_ptr<Game> &game) {
            //     return game->getInviteCode() == stoi(words[1]);
            // });
            // if (requestedGame != sessions.end())
            // {
            //     std::cout << "user has requested to leave a game" << std::endl;
            //     auto user = std::find_if(begin(users), end(users),
            //                              [message](Users &user) { return user.getConnection() == message.connection; });
            //     if (user != users.end())
            //     {
            //         (*requestedGame)->removePlayer(*user);
            //     }
            // }
            // else
            // {
            //     std::cout << "user provided invalid invite code" << std::endl;
            // }
            break;
        }
        case Command::GAME_ID: {
            for (auto &session : sessions)
            {
                for (auto player : (*session).getPlayers())
                {
                    if (player.getConnection().id == message.connection.id)
                    {

                        auto outgoing = buildOutgoing("Your game code is " + std::to_string((*session).getInviteCode()),
                                                      std::vector<Users>{player});
                        server.send(outgoing);
                    }
                }
            }
            break;
        }
        case Command::CHAT: {
            for (auto &session : sessions)
            {
                for (auto player : session->getPlayers())
                {
                    if (player.getConnection().id == message.connection.id)
                    {
                        auto outgoing =
                            buildOutgoing(std::to_string(message.connection.id) + "> " + message.text.substr(6) + "\n",
                                          session->getPlayers());
                        server.send(outgoing);
                    }
                }
            }
            break;

        }
        default: {
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
        std::cerr << "Unable to open HTML index file:\n" << htmlLocation << "\n";
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

    auto lobby = std::make_unique<GameSession>(0000);
    sessions.push_back(std::move(lobby));

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
