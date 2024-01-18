#pragma once

#include "Rule.h"

#include <vector>

template <class T, class Function>
class Sort : public Rule
{
public:
  // accept a list and a lambda
  Sort(std::vector<T> &, Function &&);
  void execute() override;

private:
  std::vector<T> &list;
  Function cmp;
};

#include <algorithm>
template <class T, class Function>
Sort<T, Function>::Sort(std::vector<T> &list, Function &&func)
    : list(list),
      cmp(func)
{
}

template <class T, class Function>
void Sort<T, Function>::execute()
{
  std::sort(list.begin(), list.end(), cmp);
}
