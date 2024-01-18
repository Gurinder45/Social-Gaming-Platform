#pragma once

#include "Rule.h"
#include "Condition.h"

#include <vector>
#include <string>

class When : public Rule
{
public:
  void addCase(Condition *condition, std::vector<Rule *> rules);
  void execute() override;
  ~When();

private:
  struct Case
  {
    Condition *condition;
    std::vector<Rule *> rules;
  };
  std::vector<Case> cases;
};
