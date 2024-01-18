#include "ServerHandler.h"

// Helper Functions//
/**************************************************************************************************************/
std::vector<GameSession *> ServerHandler::getGameSessions()
{
    std::vector<GameSession *> sessions;
    for (auto &game : games)
    {
        auto gameSession = game.get()->getGameSession();
        sessions.push_back(gameSession);
    }

    return sessions;
}

Users *ServerHandler::getUserFromConnection(Connection c)
{
    for (auto &user : users)
    {
        if (user.getConnection().id == c.id)
        {
            return &user;
        }
    }
    std::cout << "User not found" << std::endl;
    return nullptr;
}

// Modify ServerHandler Data //
/***********************************************************************************************************/
void ServerHandler::addClient()
{
}

void ServerHandler::addGame(std::unique_ptr<Game> game)
{
    games.push_back(std::move(game));
}

void ServerHandler::addUser(Users user)
{
    users.push_back(user);
}

void ServerHandler::removeClient(Connection connection)
{
    auto eraseBegin = std::remove(std::begin(clients), std::end(clients), connection);
    clients.erase(eraseBegin, std::end(clients));
}

// Send Messages //
/**************************************************************************************************************/
std::deque<Message> ServerHandler::buildOutgoing(const std::string &log, std::vector<Users> userList)
{
    std::deque<Message> outgoing;
    for (auto user : userList)
    {
        outgoing.push_back({user.getConnection(), log});
    }
    return outgoing;
}

// Command Executions //
/**************************************************************************************************************/
void ServerHandler::createGame(const Message &message, Server &server)
{
    addGame(std::make_unique<Game>());
    auto gamesSize = games.size();
    auto gameSessions = getGameSessions();
    auto lastGameSessionInviteCode = gameSessions.back()->getInviteCode();

    std::cout << "Request to create game received from client: " << message.connection.id << std::endl;
    std::cout << "Current number of games: " << gamesSize << std::endl;
    std::cout << "A new game has been created with invite code: " << lastGameSessionInviteCode << std::endl;
    std::cout << "/---------------------------------------------------------------/" << std::endl;

    auto user = getUserFromConnection(message.connection);
    if (!user)
    {
        return;
    }

    auto outgoingMessage = "You created a game with code: " + std::to_string(lastGameSessionInviteCode);
    auto outgoing = (buildOutgoing(outgoingMessage, std::vector<Users>{*user}));
    server.send(outgoing);
}

void ServerHandler::disconnectFromServer(const Message &message, Server &server) const
{
    server.disconnect(message.connection);
}

void ServerHandler::changeUsername(const Message &message, Server &server, std::string_view newUsername)
{
    auto user = getUserFromConnection(message.connection);

    if (!user)
    {
        std::cout << "Couldn't find a connection somehow..." << std::endl;
        return;
    }

    user->changeUsername(newUsername);
    std::cout << "Succesfully changed username for " << message.connection.id << " to "
              << user->GetUsername() << std::endl;

    auto username = user->GetUsername();
    std::vector<Users> userList{*user};

    auto outgoing = buildOutgoing("You have changed your username to " + username, userList);
    server.send(outgoing);
}

void ServerHandler::leaveGame(const Message &message, Server &server, std::string_view inviteCode)
{
    auto requestedGame = std::find_if(std::begin(games), std::end(games), [inviteCode](std::unique_ptr<Game> &game)
                                      {
                auto session = game.get()->getGameSession();
                auto sessionInviteCode = std::to_string(session->getInviteCode());
                return sessionInviteCode == inviteCode; });

    auto game = requestedGame->get();
    if (game == NULL)
    {
        std::cout << "Sorry, a game with that invite code doesn't exist. Please try again" << std::endl;
        std::cout << "/---------------------------------------------------------------/" << std::endl;
        return;
    }

    auto requestedSession = game->getGameSession();
    auto gameSessions = getGameSessions();

    if (std::find(gameSessions.begin(), gameSessions.end(), requestedSession) != gameSessions.end())
    {
        std::cout << "user has requested to leave a game" << std::endl;
        auto user = getUserFromConnection(message.connection);

        if (!user)
        {
            return;
        }

        requestedSession->removePlayer(*user);
        auto outgoingMessage = (*user).GetUsername() + " has left their game\n";
        auto outgoing = buildOutgoing(outgoingMessage, requestedSession->getPlayers());
        server.send(outgoing);
    }
}

void ServerHandler::joinGame(const Message &message, Server &server, std::string_view inviteCode)
{
    auto requestedGame = std::find_if(std::begin(games), std::end(games), [inviteCode](std::unique_ptr<Game> &game)
                                      {
                auto session = game.get()->getGameSession();
                auto sessionInviteCode = std::to_string(session->getInviteCode());
                return sessionInviteCode == inviteCode; });

    auto game = requestedGame->get();
    if (game == NULL)
    {
        std::cout << "Sorry, a game with that invite code doesn't exist. Please try again" << std::endl;
        std::cout << "/---------------------------------------------------------------/" << std::endl;
        return;
    }

    auto requestedSession = game->getGameSession();
    auto gameSessions = getGameSessions();

    if (std::find(gameSessions.begin(), gameSessions.end(), requestedSession) != gameSessions.end())
    {
        std::cout << "user has requested to join a game that is available!" << std::endl;
        auto user = getUserFromConnection(message.connection);

        if (!user)
        {
            return;
        }

        requestedSession->addPlayer(*user);
        auto outgoingMessage = (*user).GetUsername() + " has joined the game\n";
        auto outgoing = buildOutgoing(outgoingMessage, requestedSession->getPlayers());
        server.send(outgoing);
    }
}

void ServerHandler::showGameId(const Message &message, Server &server)
{
    auto gameSessions = getGameSessions();

    for (auto &session : gameSessions)
    {
        for (auto &player : session->getPlayers())
        {
            if (player.getConnection().id == message.connection.id)
            {
                std::vector<Users> user{player};
                const auto outgoingMessage = "Your game code is " + std::to_string((*session).getInviteCode());
                auto outgoing = buildOutgoing(outgoingMessage, user);
                server.send(outgoing);
                return;
            }
        }
    }
}

void ServerHandler::printChatMessage(const Message &message, Server &server)
{
    auto gameSessions = getGameSessions();
    for (auto &session : gameSessions)
    {
        for (auto player : session->getPlayers())
        {
            if (player.getConnection().id == message.connection.id)
            {
                auto outgoingMessage = std::to_string(message.connection.id) + "> " + message.text.substr(6) + "\n";
                auto outgoing = buildOutgoing(outgoingMessage, session->getPlayers());
                server.send(outgoing);
                return;
            }
        }
    }
}

void ServerHandler::addGame(const Message &message)
{
    bool isUserInGameSession = false;
    Game *userGame;
    for (auto &game : games)
    {
        auto gameSession = game.get()->getGameSession();
        auto users = gameSession->getPlayers();

        auto user = std::find_if(users.begin(), users.end(),
                                 [message](auto &user)
                                 { return user.getConnection() == message.connection; });

        if (user != users.end())
        {
            userGame = game.get();
            isUserInGameSession = true;
            break;
        }
    }

    if (!isUserInGameSession)
    {
        std::cout << "User is currently not in a game session. Join a session first.";
        std::cout << "/---------------------------------------------------------------/" << std::endl;
        return;
    }
    std::string response = userGame->getConfigFromFile("lib/web-socket-networking/tools/chatserver/testGame.json");
    auto userGameSession = userGame->getGameSession();
    auto userGameInviteCode = userGameSession->getInviteCode();
    std::cout << response << " Basic game created for Game with invite code:" << userGameInviteCode << std::endl;
    std::cout << "/---------------------------------------------------------------/" << std::endl;
}

void ServerHandler::invalidCommand()
{
    std::cout << " Command is invalid. Please try again:" << std::endl;
    std::cout << "/---------------------------------------------------------------/" << std::endl;
}

void ServerHandler::showGameInfo(const Message &message, Server &server)
{
    for (auto &game : games)
    {
        auto gameSession = game.get()->getGameSession();
        auto users = gameSession->getPlayers();

        auto user = std::find_if(users.begin(), users.end(),
                                 [message](auto &user)
                                 { return user.getConnection() == message.connection; });

        if (user != users.end())
        {
            auto userGame = game.get();
            auto gameConfig = userGame->getGameConfig();
            auto gameSession = userGame->getGameSession();
            auto gameName = gameConfig->getName();
            std::vector<Users> currentUser{*user};

            auto outgoingMessage = ("Game Name: " + gameName);

            auto outgoing = buildOutgoing(outgoingMessage, currentUser);
            server.send(outgoing);
            break;
        }
    }
}

void ServerHandler::startGame(const Message &message, Server &server)
{
    for (auto &game : games)
    {
        auto gameSession = game.get()->getGameSession();
        auto users = gameSession->getPlayers();

        auto user = std::find_if(users.begin(), users.end(),
                                 [message](auto &user)
                                 { return user.getConnection() == message.connection; });

        if (user != users.end())
        {
            auto userGame = game.get();
            auto gameConfig = userGame->getGameConfig();
            auto gameSession = userGame->getGameSession();
            auto gameName = gameConfig->getName();

            std::vector<std::unique_ptr<Rule>> const& rules = userGame->rules;
            for (auto &rule : rules)
            {
                rule.get()->execute();

                /** @TODO: REMOVE TEST CODE */
                std::string outgoingMessage = "Hello World!";
                auto outgoing = buildOutgoing(outgoingMessage, users);
                server.send(outgoing);
            }
            return;
        }
    }
}

void ServerHandler::getLastMessage(const Message &message, Server &server)
{
    auto gameSessions = getGameSessions();
    for (auto &session : gameSessions)
    {
        for (auto player : session->getPlayers())
        {
            if (player.getConnection().id == message.connection.id)
            {
                auto outgoing = buildOutgoing(lastMessages[message.connection.id] + "\n", std::vector<Users>{player});
                server.send(outgoing);
                return;
            }
        }
    }
}