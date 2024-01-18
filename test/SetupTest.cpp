#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "VarPool.h"
#include "GameConfig.h"
#include "Game.h"

#include <string>

using namespace testing;

class SetupTest : public testing::Test
{

public:

    std::unique_ptr<GameConfig> gameConfig;

    SetupTest()
    {
        gameConfig = std::make_unique<GameConfig>();
    }

    ~SetupTest()
    {
    }
};

// This test requires input in the form of a string. To test the getQuestionAnswers method, uncomment the code below.
TEST_F(SetupTest, addVarPoolQuestion)
{
    auto mathQuestionName = "Square Question";
    auto mathQuestion = "Whats the square of 2?";

    gameConfig->addQuestion(mathQuestionName, mathQuestion);

    // gameConfig->getQuestionAnswers();

    // auto mathQuestionValue = gameConfig->getString(mathQuestionName)->get();
    // auto expectedAnswer = "4"; // Place expected answer here
    // EXPECT_EQ(mathQuestionValue, expectedAnswer);
}

// This test requires input in the form of a string. To test the getMultipleChoice method, uncomment the code below.
TEST_F(SetupTest, addVarPoolMultipleChoice)
{
    auto multipleChoiceName = "What is the value of 1?";
    std::vector<std::string> choices = { 
      "1",
      "2",
      "3",
      "4",
    };

    gameConfig->addMultipleChoice(multipleChoiceName, choices);

//     gameConfig->getMultipleChoiceAnswer();

//     auto mathQuestionNameType = gameConfig->getString(multipleChoiceName)->get();
//     auto expectedAnswer = "1"; // Place expected answer here
//     EXPECT_EQ(mathQuestionNameType, expectedAnswer);
}