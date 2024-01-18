#pragma once

#include "Rule.h"
#include "BasicInput.h"

#include <string>

class InputChoice : public BasicInput
{
public:
  void timeout() override;
  void prompt() override;
};
