#include "Add.h"

Add::Add(int &to, int value)
    : Rule(),
      to(to),
      value(value)
{
}

void Add::execute()
{
  to += value;
}

std::unique_ptr<Rule> Add::parse(json data, std::shared_ptr<GameConfig> &configurations)
{

  int &to_add = configurations->getInt(data["to"].get<std::string>()).value();

  int value;

  if(data["value"].is_number())
    value = data["value"].get<int>();
  else
    value = configurations->getInt(data["value"].get<std::string>()).value();


  return std::make_unique<Add>(to_add, value);
}