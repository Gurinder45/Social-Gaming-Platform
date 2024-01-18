#include "Rule.h"
#include "Rules.h"
#include "Add.h"
#include "Foreach.h"
#include "Timer.h"
#include "InputChoice.h"
#include "InputText.h"
#include "InputVote.h"
#include "GlobalMessage.h"
// #include "Message.h"
#include "Scores.h"
#include "Foreach.h"
#include "Loop.h"
#include "InParallel.h"
#include "ParallelFor.h"
#include "Switch.h"
#include "When.h"
#include "Condition.h"
#include "Extend.h"
#include "Reverse.h"
#include "Shuffle.h"
#include "Sort.h"
#include "Deal.h"
#include "Discard.h"

Rule::Rule() {};

// helper function to parse rules from json
std::unique_ptr<Rule> parseRules(json data, GameConfig& configurations, GameSession &gameSession)
{

    std::unique_ptr<Rule> r;
    std::string rule = data["rule"].get<std::string>();
    if (rule == "add")
    {
        // r = Add::parse(data, configurations);
    }
    else if (rule == "timer")
    {
        // r = Timer::parse(data, configurations);
    }

    // input
    else if (rule == "input-choice")
    {
        // r = InputChoice::parse(data, configurations);
    }
    else if (rule == "input-text")
    {
        // r = InputText::parse(data, configurations);
    }
    else if (rule == "input-vote")
    {
        // r = InputVote::parse(data, configurations);
    }

    // output
    else if (rule == "global-message")
    {
        r = GlobalMessage::parse(data, configurations, gameSession);
    }
    else if (rule == "message")
    {
        // r = Message::parse(data, configurations);
    }
    else if (rule == "scores")
    {
        // r = Scores::parse(data, configurations);
    }

    // control
    else if (rule == "foreach")
    {
        // r = parseForeach(data, configurations);
    }
    else if (rule == "loop")
    {
        // r = parseLoop(data, configurations);
    }
    else if (rule == "inparallel")
    {
        // r = parseInParallel(data, configurations);
    }
    else if (rule == "parallelfor")
    {
        // r = parseParallelFor(data, configurations);
    }
    else if (rule == "switch")
    {
        // r = Switch::parse(data, configurations);
    }
    else if (rule == "when")
    {
        // r= When::parse(data, configurations);
    }
    else if (rule == "condition")
    {
        // r = Condition::parse(data, configurations);
    }

    // list rule
    else if (rule == "extend")
    {
        // r = Extend::parse(data, configurations);
    }
    else if (rule == "reverse")
    {
        // r = Reverse::parse(data, configurations);
    }
    else if (rule == "shuffle")
    {
        // r = Shuffle::parse(data, configurations);
    }
    else if (rule == "sort")
    {
        // r = Sort::parse(data, configurations);
    }
    else if (rule == "deal")
    {
        // r = Deal::parse(data, configurations);
    }
    else if (rule == "discard")
    {
        // r = Discard::parse(data, configurations);
    }

    return r;
}
