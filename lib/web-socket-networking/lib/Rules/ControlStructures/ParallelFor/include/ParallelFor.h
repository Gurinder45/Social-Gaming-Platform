#include "Rule.h"

#include <vector>
#include <string>

template <typename T>
class ParallelFor : public Rule
{
public:
  ParallelFor(std::reference_wrapper<std::vector<T>> list, std::string element, GameConfig &config);
  void addRule(std::unique_ptr<Rule> rule);
  void execute() override;

protected:
  std::string element;
  std::reference_wrapper<std::vector<T>> list;
  std::vector<std::unique_ptr<Rule>> rules;
  GameConfig &config;
};

template <typename T>
ParallelFor<T>::ParallelFor(std::reference_wrapper<std::vector<T>> list, std::string element, GameConfig &config)
    : list(list),
      element(element),
      config(config)
{
}

template <typename T>
void ParallelFor<T>::addRule(std::unique_ptr<Rule> rule)
{
  rules.push_back(rule);
}

template <typename T>
void ParallelFor<T>::execute()
{
  for (auto &element : list.get())
  {
    // update the variable value and execute the rules
    // this->config.setVar(this->element, element);
    // for (auto &rule : this->rules)
    // {
    //   std::thread t([rule]
    //                 { rule->execute(); });
    //   t.detach();
    // }
  }

  config.removeVar(this->element);
}

// std::unique_ptr<Rule> parseParallelFor(json data, std::shared_ptr<GameConfig> &configurations)
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

//   return std::make_unique<ParallelFor<VarPool>>(list, element, *configurations);
// }
