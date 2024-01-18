#include "ParallelFor.h"
#include <thread>

// void ParallelFor::addRule(Rule *rule)
// {
//   rules.push_back(rule);
// }

// void ParallelFor::execute()
// {
//   for (Rule *rule : this->rules)
//   {
//     std::thread t([rule]
//                   { rule->execute(); });
//     t.detach();
//   }
// }
