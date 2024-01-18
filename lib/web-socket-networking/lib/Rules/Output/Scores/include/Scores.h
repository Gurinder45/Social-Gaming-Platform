#pragma once

#include "Rule.h"

class Scores : public Rule
{
public:
  Scores(int score, bool ascending);

private:
  int score;
  bool ascending;
};
