#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "../../VarPool/include/VarPool.h"
#include "GameConfig.h"
#include "Game.h"

#include <string>

using namespace testing;

class GameConfigTest : public testing::Test
{

public:

    std::unique_ptr<GameConfig> gameConfig;

    GameConfigTest()
    {
        gameConfig = std::make_unique<GameConfig>();
    }

    ~GameConfigTest()
    {
    }
};

// PKc represents a string and may be compiler specific.
TEST_F(GameConfigTest, addVarPoolVariableString)
{
    auto varName = "WeaponType";
    auto varValue = "Rock";

    gameConfig->addVar(varName, varValue);
    auto varValueResult = gameConfig->getType("WeaponType");
    EXPECT_EQ(varValueResult, "PKc");

    EXPECT_TRUE(gameConfig->exists(varName));
    EXPECT_FALSE(gameConfig->exists("HandSize"));
}

TEST_F(GameConfigTest, addIntegerVarPoolVariable)
{
    auto varName = "Integer";
    auto varValue = 3;

    gameConfig->addVar(varName, varValue);
    auto varValueResult = gameConfig->getVarPoolValue<int>(varName);
    EXPECT_EQ(varValueResult, 3);

    EXPECT_TRUE(gameConfig->exists(varName));

    auto invalidVarName = "Numbers";
    EXPECT_FALSE(gameConfig->exists(invalidVarName));
}

TEST_F(GameConfigTest, addDoubleVarPoolVariable)
{
    auto varName = "Double";
    auto varValue = 3.5;

    gameConfig->addVar(varName, varValue);
    auto varValueResult = gameConfig->getVarPoolValue<double>(varName);
    EXPECT_EQ(varValueResult, varValue);

    EXPECT_TRUE(gameConfig->exists(varName));
    EXPECT_FALSE(gameConfig->exists("Numbers"));
}

TEST_F(GameConfigTest, addIntegerListVariable)
{
    auto varName = "IntegerList";
    std::vector<int> integerList = {1, 2, 3, 4};

    gameConfig->addVar(varName, integerList);
    EXPECT_TRUE(gameConfig->exists(varName));

    auto varType = gameConfig->getVarPoolValue<std::vector<int>>(varName);
    EXPECT_EQ(varType->get(), integerList);

}

TEST_F(GameConfigTest, addDoubleListVariable)
{
    auto varName = "DoubleList";
    std::vector<double> doubleList = {1.0, 2.2, 3.9, 6.8};

    gameConfig->addVar(varName, doubleList);
    EXPECT_TRUE(gameConfig->exists(varName));

    auto varType = gameConfig->getVarPoolValue<std::vector<double>>(varName);
    EXPECT_EQ(varType->get(), doubleList);

}

TEST_F(GameConfigTest, addStringListVariable)
{
    auto varName = "StringList";
    std::vector<std::string> stringList = {"Car", "Truck", "SUV", "Van"};

    gameConfig->addVar(varName, stringList);
    EXPECT_TRUE(gameConfig->exists(varName));

    auto varType = gameConfig->getVarPoolValue<std::vector<std::string>>(varName);
    EXPECT_EQ(varType->get(), stringList);

}