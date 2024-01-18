#include "RuleParser.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <fstream>

class RuleParserTest : public ::testing::Test{
protected:
    RuleParser* ruleParser;
    void SetUp() override{
        ruleParser = new RuleParser();
    }
    void TearDown() override{
        delete ruleParser;
    }
};

TEST_F (RuleParserTest, parseRulesFromNonExistentFile){
    RuleParser::ParseResult result = ruleParser->parseRulestoVarpool("t0stG4me.json");
    EXPECT_EQ(result, RuleParser::ParseResult::PARSE_FAIL);
}


TEST_F (RuleParserTest, parseRulesFromEmptyJSONRule){
    RuleParser::ParseResult result = ruleParser->parseRulestoVarpool("../test/testGame.json");
    EXPECT_EQ(result, RuleParser::ParseResult::PARSE_FAIL);
}
