#include <Condition.h>

Condition::Condition(std::string condition, GameConfig &config)
    : condition(condition),
      config(config)
{
}

bool Condition::evaluate()
{
    /** @TODO: implement
    // parse the condition , get neccesary values of the variables using gameconfig
    // and evaluate it
    */

    return true;
}
