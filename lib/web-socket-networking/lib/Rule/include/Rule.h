#pragma once
#include <iostream>
#include "GameConfig.h"
#include "GameSession.h"

class Rule
{
public:
  Rule();
  virtual void execute()=0;


  // virtual
  static std::unique_ptr<Rule> parse(json data, GameConfig& configurations, GameSession& gameSession)
  {
    return nullptr;
  }

};

//parses rule from the json data
std::unique_ptr<Rule> parseRules(json data, GameConfig& configurations, GameSession& gameSession);