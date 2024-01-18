#include "Message.h"

Message::Message(std::string to, std::string value)
    : Rule(),
      to(to),
      value(value)
{
}
