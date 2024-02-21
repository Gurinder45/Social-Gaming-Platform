#pragma once

#include "Rule.h"
#include "GameConfig.h"

#include <vector>
#include <string>

template <typename T>
class Foreach : public Rule
{
public:
  /** TODO: replace string list with a list, list expression, or name of a list object
   * In the future, may want to use a deque instead of a list for rules
   */
  Foreach(std::vector<T> &list, std::string element, GameConfig &config);
  void addRule(std::unique_ptr<Rule> rule);
  virtual void execute() override;
  static std::unique_ptr<Rule> parse(json data, std::shared_ptr<GameConfig> &configurations);

protected:
  std::string element;
  std::vector<T> &list;
  std::vector<std::unique_ptr<Rule>> rules;
  GameConfig &config;
};

template <typename T>
std::unique_ptr<Rule> Foreach<T>::parse(json data, std::shared_ptr<GameConfig> &configurations)
{

  std::string name;
  if (data["list"].is_string())
  {
    name = data["list"].get<std::string>();
  }
  else
  {

    name = "tmplist-" + rand() % 100;
    json tmp = {{name, data["list"]}};
    configurations->addList(tmp);
  }

  std::string element = data["element"].get<std::string>();

  std::vector<T> &list = configurations->getList<T>(name);

  auto foreach = std::make_unique<Foreach<T>>(list, element, *configurations);

  for (auto &rule : data["rules"])
  {
    foreach
      ->addRule(parseRules(rule, configurations));
  }

  return foreach;
}

template <typename T>
Foreach<T>::Foreach(std::vector<T> &list, std::string element, GameConfig &config)
    : Rule({}), list(list), element(element),
      config(config)
{
}

template <typename T>
void Foreach<T>::addRule(std::unique_ptr<Rule> rule)
{
  rules.push_back(rule);
}

template <typename T>
void Foreach<T>::execute()
{
  for (auto &element : list)
  {
    // update the variable value and execute the rules
    this->config.setVar(this->element, element);
    for (auto &rule : rules)
    {
      rule->execute();
    }
  }

  config.removeVar(this->element);
}
