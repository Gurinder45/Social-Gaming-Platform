#pragma once

#include "Rule.h"

#include <vector>
#include <string>

template <class T>
class Switch : public Rule
{
public:
  Switch(T value, std::vector<T> &allowableValues);
  void addCase(T value, std::vector<Rule *> rules);
  void execute() override;

private:
  struct Case
  {
    T value;
    std::vector<Rule *> rules;
  };
  std::vector<T> &allowableValues;
  std::vector<Case> cases;
  T value;
};

template <class T>
Switch<T>::Switch(T value, std::vector<T> &allowableValues)
    : value(value), allowableValues(allowableValues)
{
}

template <class T>
void Switch<T>::addCase(T value, std::vector<Rule *> rules)
{
  auto it = std::find(allowableValues.begin(), allowableValues.end(), value);
  if (it == allowableValues.end())
    throw std::invalid_argument("Value not in allowable values");

  Case newCase;
  newCase.value = value;
  newCase.rules = rules;
  cases.push_back(std::move(newCase));
}

template <class T>
void Switch<T>::execute()
{
  for (auto &switchCase : cases)
  {
    if (switchCase.value == value)
    {
      for (auto &rule : switchCase.rules)
      {
        rule->execute();
      }
      return;
    }
  }
}
