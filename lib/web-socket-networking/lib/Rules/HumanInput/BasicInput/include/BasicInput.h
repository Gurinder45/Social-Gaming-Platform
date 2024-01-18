#pragma once

#include "Rule.h"
// #include "users.h"

class BasicInput : public Rule
{
public:
    BasicInput(Users &users, std::string prompt);
    BasicInput(Users &users, std::string prompt, clock_t t);
    virtual void execute() = 0;

    virtual void timeout() = 0;
    virtual void prompt() = 0;

protected:
    clock_t timeout_delay;
    Users &to;
    std::string prompt_msg;
};
