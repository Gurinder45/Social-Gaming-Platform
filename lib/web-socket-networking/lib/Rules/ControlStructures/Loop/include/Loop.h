#pragma once

#include "Rule.h"
#include "Condition.h"

#include <vector>
#include <string>

class Loop : public Rule
{
public:
  /** TODO: replace isUntil and isWhile with the actual conditions in the future */
  Loop(Condition condition);
  void addRule(Rule *rule);
  void execute() override;

private:
  Condition condition;
  std::vector<Rule *> rules;
};


// std::unique_ptr<Rule> parseLoop(json data, std::shared_ptr<GameConfig> &configurations)
// {
//   Condition condition("string", *configurations);
//   return std::make_unique<Loop>(condition);
// }
