#pragma once

#include "Rule.h"
#include "Foreach.h"

#include <vector>
#include <string>
#include <thread>

template <typename T>
class InParallel : public Rule
{
public:
  InParallel(std::reference_wrapper<std::vector<T>> list, std::string element, GameConfig &config);
  void addRule(std::unique_ptr<Rule> rule);
  void execute() override;

protected:
  std::string element;
  std::reference_wrapper<std::vector<T>> list;
  std::vector<std::unique_ptr<Rule>> rules;
  GameConfig &config;
};

template <typename T>
InParallel<T>::InParallel(std::reference_wrapper<std::vector<T>> list, std::string element, GameConfig &config)
    : list(list),
      element(element),
      config(config)
{
}

template <typename T>
void InParallel<T>::addRule(std::unique_ptr<Rule> rule)
{
  rules.push_back(rule);
}


template <typename T>
void InParallel<T>::execute()
{
  for (auto &element : this->list.get())
  {
    //update the variable value and execute the rules
    // this->config.setVariable(this->element, element);


    // std::vector<std::thread> threads;

    // for (auto &rule : this->rules)
    // {
    //   std::thread t([rule](){
    //     rule->execute();
    //   });
    //   threads.push_back(std::move(t));
    // }

    // for (auto &t : threads)
    //   t.join();
  }

  this->config.removeVar(this->element);
}

// std::unique_ptr<Rule> parseInParallel(json data, std::shared_ptr<GameConfig> &configurations)
// {
//   std::string name;
//   if (data["list"].is_string())
//   {
//     name = data["list"].get<std::string>();
//   }
//   else
//   {
//     name = "tmplist-" + rand() % 100;
//     json tmp = {{name, data["list"]}};
//     configurations->addJson(tmp);
//   }

//   std::string element = data["element"].get<std::string>();
//   std::reference_wrapper<std::vector<VarPool>> list = configurations->getList(name).value();

//   return std::make_unique<InParallel<VarPool>>(list, element, *configurations);
// }
