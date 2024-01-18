#include "RuleParser.h"
#include <fstream>
#include <iostream>
using json = nlohmann::json;

RuleParser::RuleParser(){
    // TODO: Constructor
}


RuleParser::ParseResult RuleParser::parseRules(const nlohmann::json& rules){
    std::ifstream file(rules);
    if(!file.is_open()){
        return PARSE_FAIL;
    }
    json j;
    file >> j;
    file.close();

    // Parse rules
    if(!j.contains("rules")){
        return PARSE_FAIL;
    }
    if(this->parseRules(j["rules"])!=RuleParser::PARSE_SUCCESS){
        return PARSE_FAIL;
    }

    return PARSE_SUCCESS;
}


RuleParser::ParseResult RuleParser::parseRulestoVarpool(std::string fileName)
{
    json data;

    if(verifyJson(fileName)){
        // take the file and parse it into a json object
        std::ifstream file(fileName);
        file >> data;
        file.close();
    }
    else{
        return PARSE_FAIL;
    }

    // Get rule variable from json data
    std::string rule = data["rule"].get<std::string>();

    // will Store string as value and int as key to the VarPool pool map
    if (rule == "add")
    {
        std::string varName = "Rule_add";
        auto ruleInt = this->getInt(rule);
        addVar(varName, ruleInt);
        return PARSE_SUCCESS;
    }
    else if (rule == "timer")
    {
        std::string varName = "Rule_timer";
        auto ruleInt = this->getInt(rule);
        addVar(varName, ruleInt);
        return PARSE_SUCCESS;
    }

    // input
    else if (rule == "input-choice")
    {
        std::string varName = "Rule_input-choice";
        auto ruleInt = this->getInt(rule);
        addVar(varName, ruleInt);
        return PARSE_SUCCESS;
    }
    else if (rule == "input-text")
    {
        std::string varName = "Rule_input-text";
        auto ruleInt = this->getInt(rule);
        addVar(varName, ruleInt);
        return PARSE_SUCCESS;
    }
    else if (rule == "input-vote")
    {
        std::string varName = "Rule_input-vote";
        auto ruleInt = this->getInt(rule);
        addVar(varName, ruleInt);
        return PARSE_SUCCESS;
    }
    else if (rule == "message")
    {
        std::string varName = "Rule_message";
        auto ruleInt = this->getInt(rule);
        addVar(varName, ruleInt);
        return PARSE_SUCCESS;
    }
    else if (rule == "scores")
    {
        std::string varName = "Rule_scores";
        auto ruleInt = this->getInt(rule);
        addVar(varName, ruleInt);
        return PARSE_SUCCESS;
    }

    // control
    else if (rule == "foreach")
    {
        std::string varName = "Rule_foreach";
        auto ruleInt = this->getInt(rule);
        addVar(varName, ruleInt);
        return PARSE_SUCCESS;
    }
    else if (rule == "loop")
    {
        std::string varName = "Rule_loop";
        auto ruleInt = this->getInt(rule);
        addVar(varName, ruleInt);
        return PARSE_SUCCESS;
    }
    else if (rule == "global-message")
    {
        std::string varName = "Rule_global-message";
        auto ruleInt = this->getInt(rule);
        addVar(varName, ruleInt);
        return PARSE_SUCCESS;
    }
    else if (rule == "inparallel")
    {
        std::string varName = "Rule_inparallel";
        auto ruleInt = this->getInt(rule);
        addVar(varName, ruleInt);
        return PARSE_SUCCESS;
    }
    else if (rule == "parallelfor")
    {
        std::string varName = "Rule_parallelfor";
        auto ruleInt = this->getInt(rule);
        addVar(varName, ruleInt);
        return PARSE_SUCCESS;
    }
    else if (rule == "switch")
    {
        std::string varName = "Rule_switch";
        auto ruleInt = this->getInt(rule);
        addVar(varName, ruleInt);
        return PARSE_SUCCESS;
    }
    else if (rule == "when")
    {
        std::string varName = "Rule_when";
        auto ruleInt = this->getInt(rule);
        addVar(varName, ruleInt);
        return PARSE_SUCCESS;
    }
    else if (rule == "condition")
    {
        std::string varName = "Rule_condition";
        auto ruleInt = this->getInt(rule);
        addVar(varName, ruleInt);
        return PARSE_SUCCESS;
    }

    // list rule
    else if (rule == "extend")
    {
        std::string varName = "Rule_extend";
        auto ruleInt = this->getInt(rule);
        addVar(varName, ruleInt);
        return PARSE_SUCCESS;
    }
    else if (rule == "reverse")
    {
        std::string varName = "Rule_reverse";
        auto ruleInt = this->getInt(rule);
        addVar(varName, ruleInt);
        return PARSE_SUCCESS;
    }
    else if (rule == "shuffle")
    {
        std::string varName = "Rule_shuffle";
        auto ruleInt = this->getInt(rule);
        addVar(varName, ruleInt);
        return PARSE_SUCCESS;
    }
    else if (rule == "sort")
    {
        std::string varName = "Rule_sort";
        auto ruleInt = this->getInt(rule);
        addVar(varName, ruleInt);
        return PARSE_SUCCESS;
    }
    else if (rule == "deal")
    {
        std::string varName = "Rule_deal";
        auto ruleInt = this->getInt(rule);
        addVar(varName, ruleInt);
        return PARSE_SUCCESS;
    }
    else if (rule == "discard")
    {
        std::string varName = "Rule_discard";
        auto ruleInt = this->getInt(rule);
        addVar(varName, ruleInt);
        return PARSE_SUCCESS;
    }
    
    return PARSE_FAIL;
}

bool RuleParser::verifyJson(std::string fileName)
{
    // Check if file exists
    std::ifstream file(fileName, std::ifstream::binary);
    if (!file.is_open())
    {
        std::cout << "File does not exist" << std::endl;
        return false;
    }

    // Check if file is empty
    if (file.peek() == std::ifstream::traits_type::eof())
    {
        std::cout << "File is empty" << std::endl;
        return false;
    }

    // Check if file is valid json
    json data;
    try
    {
        file >> data;
    }
    catch (json::parse_error& e)
    {
        std::cout << "File is not valid json" << std::endl;
        return false;
    }
}


