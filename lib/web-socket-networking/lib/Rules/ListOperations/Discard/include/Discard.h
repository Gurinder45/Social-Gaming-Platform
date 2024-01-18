#pragma once

#include "Rule.h"

#include <string>
#include <vector>

template <class T>
class Discard : public Rule
{
public:
  /** transfers count elements from the begininh of 'from'
   list to end of the to list*/
  Discard(std::vector<T> &from, int count);
  void execute() override;

private:
  std::vector<T> &from;
  int count;
};

template <class T>
Discard<T>::Discard(std::vector<T> &from, int count)
    : from(from), count(count)
{
}

template <class T>
void Discard<T>::execute()
{
  from.erase(from.end() - count, from.end());
}
