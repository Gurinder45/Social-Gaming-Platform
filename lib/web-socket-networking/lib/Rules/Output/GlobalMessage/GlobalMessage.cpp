#include "GlobalMessage.h"

GlobalMessage::GlobalMessage(std::string value, std::vector<Users> &users)
    : value{value}, users{users}
{
}

void GlobalMessage::execute()
{
  std::deque<Message> outgoing;
  std::for_each(users.begin(), users.end(), [&outgoing, &value = value](auto &usr)
                { outgoing.push_back({usr.getConnection(), value}); });
}

std::unique_ptr<Rule> GlobalMessage::parse(json data, GameConfig &configurations, GameSession &gameSession)
{

  // std::string messageValue = data["rules"]["value"].get<std::string>();
  std::string messageValue = "Hello World!";

  auto allGameUsers = gameSession.getPlayers();

  return std::make_unique<GlobalMessage>(messageValue, allGameUsers);
}
