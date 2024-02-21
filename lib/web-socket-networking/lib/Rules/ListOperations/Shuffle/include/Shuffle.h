#pragma once

#include "Rule.h"

#include <vector>

template <class T>
class Shuffle : public Rule
{
public:
  Shuffle(std::vector<T> &);
  void execute() override;

private:
  std::vector<T> &list;
};

#include <algorithm>
template <class T>
Shuffle<T>::Shuffle(std::vector<T> &list)
    : Rule({}),
      list(list)
{
}

template <class T>
void Shuffle<T>::execute()
{
  std::shuffle(list.begin(), list.end());
}
