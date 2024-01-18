#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <string>
#include <iostream>
#include "GameParser.h"

using namespace testing;

class GameParserTest : public testing::Test
{

public:
    std::unique_ptr<GameParser> parser;

    GameParserTest() {
        parser = std::make_unique<GameParser>();
    }

    ~GameParserTest() {
    }
};

TEST_F(GameParserTest, parseGameConfigRockPaperScissors)
{
    parser->modifyGamePath(GameParser::GameOptions::ROCK_PAPER_SCISSORS, "../test/RockPaperScissors.json");
    GameParser::ParseResult result = parser->validateSaveGameConfig(GameParser::GameOptions::ROCK_PAPER_SCISSORS);
    EXPECT_EQ(result, GameParser::ParseResult::PARSE_SUCCESS);
    EXPECT_EQ(parser->getName(), "Rock, Paper, Scissors");
    EXPECT_EQ(parser->getAudience(), false);
    EXPECT_EQ(parser->getMinPlayers(), 2);
    EXPECT_EQ(parser->getMaxPlayers(), 4);
    EXPECT_EQ(parser->getRounds(), 10);
}

TEST_F(GameParserTest, parseGameConstantsRockPaperScissors)
{
   
}

