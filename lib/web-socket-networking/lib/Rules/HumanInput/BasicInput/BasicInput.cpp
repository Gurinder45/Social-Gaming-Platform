#include "BasicInput.h"

BasicInput::BasicInput(Users &users, std::string prompt)
    : to(users), prompt_msg(prompt)
{
    timeout_delay = 10000;
}

BasicInput::BasicInput(Users &users, std::string prompt, clock_t t)
    : to(users), prompt_msg(prompt), timeout_delay(t)
{
}
