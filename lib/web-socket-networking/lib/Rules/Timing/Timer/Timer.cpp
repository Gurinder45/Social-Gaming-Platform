#include "Timer.h"

#include <BasicInput.h>
#include <thread>
#include <ctime>
#include <chrono>

Timer::Timer(int duration, TimerType mode, GameConfig &config)
 : duration(duration), mode(mode), config(config)
{
}

Timer::Timer(int duration, TimerType mode, std::string flag_name, GameConfig &config)
 : duration(duration), mode(mode), flag_name(flag_name), config(config)
{
}

void Timer::addRule(Rule *r)
{
  rules.push_back(r);
}

void Timer::execute()
{
  duration *= CLOCKS_PER_SEC;

  if(mode==TimerType::EXACT){
    std::thread t([this](){
      begin_time = clock();
      while (clock() - begin_time < duration){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
      }


      for (auto r : rules)
      {
        r->execute();
      }
    });
    t.detach();
  }
  else if(mode==TimerType::TRACK){

    std::thread t([this](){
      begin_time = clock();
      while (clock() - begin_time < duration){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
      }

      config.getVarPoolValue<bool>(flag_name).value().get()=true;
      
    });
    t.detach();

    for (auto r : rules)
        r->execute();
  }
  else if(mode==TimerType::AT_MOST){

    for(auto r:rules)
      r->execute();

    std::thread t([this](){
      begin_time = clock();
      while (clock() - begin_time < duration){
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
      }

     for(Rule * r:rules){
        if(dynamic_cast<BasicInput*>(r)!=nullptr){
          BasicInput * b = static_cast<BasicInput*>(r);
          b->timeout();
        }
     }

    });
    t.detach();
  }
}
