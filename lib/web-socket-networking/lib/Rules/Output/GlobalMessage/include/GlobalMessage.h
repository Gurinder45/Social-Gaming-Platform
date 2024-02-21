#pragma once

#include "Rule.h"

#include <string>

class GlobalMessage : public Rule
{
public:
  /** TODO: Value is the message to be sent, figure out the type it should be */
  GlobalMessage(std::string value);

private:
  std::string value;
};
