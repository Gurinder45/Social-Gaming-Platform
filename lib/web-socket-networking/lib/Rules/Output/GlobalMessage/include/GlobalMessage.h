#pragma once

// Classes
#include "Rule.h"
// #include "users.h"

// STL
#include <string>
#include <vector>

// Using
using networking::Message;
using networking::Server;

class GlobalMessage : public Rule
{
public:
  GlobalMessage(std::string value, std::vector<Users> &users);
  void execute () override;
  static std::unique_ptr<Rule> parse(json data, GameConfig& configurations, GameSession& gameSession);

private:
  std::vector<Users> users;
  std::string value;
};
