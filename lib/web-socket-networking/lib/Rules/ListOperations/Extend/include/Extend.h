#pragma once

#include "Rule.h"

#include <vector>

template <class T>
class Extend : public Rule
{
public:
  Extend(std::vector<T> &, std::vector<T> &);
  void execute() override;

private:
  std::vector<T> &to;
  std::vector<T> &from;
};

template <class T>
Extend<T>::Extend(std::vector<T> &target, std::vector<T> &list)
    : to(target),
      from(list)
{
}

template <class T>
void Extend<T>::execute()
{
  for (T &data : from)
    to.push_back(data);
}
