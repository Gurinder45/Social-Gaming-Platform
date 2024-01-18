#include "Loop.h"

Loop::Loop(Condition condition) : condition(condition)
{
}

void Loop::addRule(Rule *rule)
{
  rules.push_back(rule);
}

void Loop::execute()
{
  while (condition.evaluate())
  {
    for (Rule *rule : this->rules)
    {
      rule->execute();
    }
  }
}
