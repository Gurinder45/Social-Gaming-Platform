#pragma once

#include "Rule.h"
#include "GameConfig.h"

#include <vector>
#include <string>

class Timer : public Rule
{
public:
  enum class TimerType
  {
    EXACT,
    AT_MOST,
    TRACK
  };
  Timer(int duration, TimerType mode, GameConfig &config);
  Timer(int duration, TimerType mode, std::string flag_name, GameConfig &config);
  void addRule(Rule *r);
  void execute() override;

private:
  int duration;
  clock_t begin_time;
  TimerType mode;
  std::string flag_name;
  std::vector<Rule *> rules;
  GameConfig &config;
};
