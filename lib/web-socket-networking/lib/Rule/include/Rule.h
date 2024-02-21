#pragma once
#include <iostream>
#include "GameConfig.h"

class Rule
{
public:
  Rule();
  virtual void execute()=0;
};

//parses rule from the json data
std::unique_ptr<Rule> parseRules(json data, std::shared_ptr<GameConfig>& configurations) ;