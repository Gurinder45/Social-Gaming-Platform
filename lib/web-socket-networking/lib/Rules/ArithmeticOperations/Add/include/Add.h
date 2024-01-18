#include "Rule.h"
#include <string>

class Add : public Rule
{
public:
  /** TODO: replace type of value with a custom type that can be an integer literal or variable name or constant */
  Add(int &to, int val);
  void execute() override;
  static std::unique_ptr<Rule> parse(json data, std::shared_ptr<GameConfig>& configurations);

private:
  int &to;
  int value;
};
