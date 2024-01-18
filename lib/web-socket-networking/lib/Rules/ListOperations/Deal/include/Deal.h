#pragma once

#include "Rule.h"

#include <string>
#include <vector>

template <class T>
class Deal : public Rule
{
public:
  /** transfers count elements from the begining of 'from'
   list to end of the to list*/
  Deal(std::vector<T> &to, std::vector<T> &from, int count);
  void execute() override;

private:
  std::vector<T> &from;
  std::vector<T> &to;
  int count;
};

template <class T>
Deal<T>::Deal(std::vector<T> &target, std::vector<T> &source, int count)
    : to(target),
      from(source), count(count)
{
}

template <class T>
void Deal<T>::execute()
{
  to.insert(to.end(), from.begin(), from.begin() + count);
  from.erase(from.begin(), from.begin() + count);
}
