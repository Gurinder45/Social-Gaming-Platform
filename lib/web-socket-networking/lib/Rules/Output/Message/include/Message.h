#pragma once

#include "Rule.h"

#include <string>

class Message : public Rule
{
public:
  /** @TODO:
   * Type of to should be a list of recipients, a Player, or Audience Member
   * Value is the message to be sent, figure out the type it should be
   */
  Message(std::string to, std::string value);

private:
  std::string to;
  std::string value;
};
