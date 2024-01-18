// STL
#include <list>
#include <vector>
#include <functional>
#include <map>

// Classes
#include "Server.h"
#include "Game.h"
// #include "users.h"

// Using
using networking::Connection;
using networking::Message;
using networking::Server;

class ServerHandler
{
public:
    ServerHandler()
    {
        serverLobby = std::move(std::make_unique<GameSession>(0000));
    };

    ~ServerHandler() = default;

    // Modify ServerHandler Data
    void addClient();
    void addGame(std::unique_ptr<Game> game);
    void addUser(Users user);
    void removeClient(Connection connection);

    // Command Executions
    void createGame(const Message &message, Server &server);
    void disconnectFromServer(const Message &message, Server &server) const;
    void changeUsername(const Message &message, Server &server, std::string_view newUsername);
    void leaveGame(const Message &message, Server &server, std::string_view inviteCode);
    void joinGame(const Message &message, Server &server, std::string_view inviteCode);
    void showGameId(const Message &message, Server &server);
    void showGameInfo(const Message &message, Server &server);
    void printChatMessage(const Message &message, Server &server);
    void addGame(const Message &message);
    void invalidCommand();
    void startGame(const Message &message, Server &server);
    void getLastMessage(const Message &message, Server &server);

    // Helper Functions
    std::vector<GameSession *> getGameSessions();
    Users *getUserFromConnection(Connection c);

    // Send Messages
    std::deque<Message> buildOutgoing(const std::string &log, std::vector<Users> userList);

private:
    std::vector<Connection> clients;
    std::vector<std::unique_ptr<Game>> games;
    std::vector<Users> users;
    std::map<int, std::string> lastMessages;
    std::unique_ptr<GameSession> serverLobby;
};
