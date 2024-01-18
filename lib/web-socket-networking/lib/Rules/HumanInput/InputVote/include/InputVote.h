#pragma once

#include "Rule.h"
#include "BasicInput.h"

#include <string>

class InputVote : public BasicInput
{
public:
  void timeout() override;
  void prompt() override;
};
