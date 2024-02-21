#pragma once

#include "Rule.h"
#include "Foreach.h"

#include <vector>
#include <string>
#include <thread>

template <typename T>
class InParallel : public Foreach<T>
{
public:
  InParallel(std::vector<T> &list, std::string element, GameConfig &config);
  void execute() override;
};

template <typename T>
void InParallel<T>::execute()
{
  for (auto &element : this->list)
  {
    //update the variable value and execute the rules
    this->config.setVariable(this->element, element);


    std::vector<std::thread> threads;

    for (auto &rule : this->rules)
    {
      
      std::thread t([rule](){
        rule->execute();
      });
      threads.push_back(std::move(t));
    }

    for (auto &t : threads)
      t.join();
  }

  this->config.removeVar(this->element);
}
