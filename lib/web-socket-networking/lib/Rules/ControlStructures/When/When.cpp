#include "When.h"

void When::addCase(Condition *cond, std::vector<Rule *> rules)
{
  Case newCase;
  newCase.condition = cond;
  newCase.rules = rules;
  cases.push_back(std::move(newCase));
}

void When::execute()
{
  for (auto &cs : cases)
  {
    if (cs.condition->evaluate())
    {
      for (auto &rule : cs.rules)
      {
        rule->execute();
      }
      return;
    }
  }
}

When::~When()
{
  for (auto &cs : cases)
  {
    delete cs.condition;
  }
}
