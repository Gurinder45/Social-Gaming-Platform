#pragma once

#include "Rule.h"

#include <vector>

template <class T>
class Reverse : public Rule
{
public:
  Reverse(std::vector<T> &);
  void execute() override;

private:
  std::vector<T> &list;
};

#include <algorithm>
template <class T>
Reverse<T>::Reverse(std::vector<T> &list)
    : list(list)
{
}

template <class T>
void Reverse<T>::execute()
{
  std::reverse(list.begin(), list.end());
}
