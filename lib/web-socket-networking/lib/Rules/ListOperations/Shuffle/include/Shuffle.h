#pragma once

#include "Rule.h"

#include <vector>
#include <algorithm>

#include <random>     
#include <chrono>
#include <random>
#include <algorithm>

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
    : 
      list(list)
{
}

template <class T>
void Shuffle<T>::execute()
{
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::shuffle(list.begin(), list.end(),std::default_random_engine(seed));
}
