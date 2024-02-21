#include "Rule.h"

#include <vector>
#include <string>

class ParallelFor : public Rule
{
public:
  void addRule(Rule *rule);
  void execute() override;

private:
  std::vector<Rule *> rules;
};
