// Test Headers
#include "gtest/gtest.h"
#include "gmock/gmock.h"

// Standard Library
#include <string>
#include <vector>
#include <iostream>
#include <cerrno>
#include <map>

// Class Headers
#include "VarPool.h"

using namespace testing;

class VarPoolTest : public testing::Test
{

public:
    std::unique_ptr<VarPool> varPool;

    VarPoolTest()
    {
        varPool = std::make_unique<VarPool>();
    }

    ~VarPoolTest()
    {
    }
};

TEST_F(VarPoolTest, addIntegerVarPoolVariable)
{
    auto varName = "Integer";
    auto varValue = 3;

    varPool->addVar(varName, varValue);
    auto varValueResult = varPool->getVarPoolValue<int>(varName);
    EXPECT_EQ(varValueResult, varValue);

    EXPECT_TRUE(varPool->exists(varName));

    auto invalidVarName = "Numbers";
    EXPECT_FALSE(varPool->exists(invalidVarName));
}

TEST_F(VarPoolTest, addDoubleVarPoolVariable)
{
    auto varName = "Double";
    auto varValue = 4.1;

    varPool->addVar(varName, varValue);
    auto varValueResult = varPool->getVarPoolValue<double>(varName);
    EXPECT_EQ(varValueResult, varValue);

    EXPECT_TRUE(varPool->exists(varName));
    EXPECT_FALSE(varPool->exists("Numbers"));
}

TEST_F(VarPoolTest, addIntegerListVariable)
{
    auto varName = "IntegerList";
    std::vector<int> integerList = {1, 2, 3, 4};

    varPool->addVar(varName, integerList);
    EXPECT_TRUE(varPool->exists(varName));

    auto varType = varPool->getVarPoolValue<std::vector<int>>(varName);
    EXPECT_EQ(varType->get(), integerList);

}

TEST_F(VarPoolTest, addDoubleListVariable)
{
    auto varName = "DoubleList";
    std::vector<double> doubleList = {1.0, 2.2, 3.9, 6.8};

    varPool->addVar(varName, doubleList);
    EXPECT_TRUE(varPool->exists(varName));

    auto varType = varPool->getVarPoolValue<std::vector<double>>(varName);
    EXPECT_EQ(varType->get(), doubleList);

}

TEST_F(VarPoolTest, addStringListVariable)
{
    auto varName = "StringList";
    std::vector<std::string> stringList = {"Apple", "Banana", "Orange", "Pear"};

    varPool->addVar(varName, stringList);
    EXPECT_TRUE(varPool->exists(varName));

    auto varType = varPool->getVarPoolValue<std::vector<std::string>>(varName);
    EXPECT_EQ(varType->get(), stringList);

}

TEST_F(VarPoolTest, addVarPoolVariableMap)
{
    auto varName = "WeaponTypes";
    std::map<std::string, int> weaponValuesMap = {{"Rock", 0}, {"Paper", 1}, {"Scissors", 2}};
    // std::map<int, int> intMapTest = {{0, 1}, {1, 2}, {2, 3}};

    varPool->addVar(varName, weaponValuesMap);
    auto varmap = varPool->getVarPoolValue<std::map<std::string, int>>(varName);
    for(auto it = varmap->get().begin(); it != varmap->get().end(); ++it)
    {
        EXPECT_EQ(it->second, weaponValuesMap[it->first]);
    }

    EXPECT_TRUE(varPool->exists(varName));
    EXPECT_FALSE(varPool->exists("HandSize"));
}

// PKc represents a string and may be compiler specific.
TEST_F(VarPoolTest, addVarPoolVariableString)
{
    std::string varName = "WeaponType";
    static std::string varValue = "Rock";

    varPool->addVar(varName, varValue);

    auto varValueResult = varPool->getVarPoolValue<std::string>(varName);
    // std::string test = std::to_string(*varValueResult);
    /** @TODO: Will need to double check implementation of getString */
    EXPECT_EQ(varValueResult->get(), varValue);

    // auto varType = varPool->getType("WeaponType");
    // EXPECT_EQ(varType, "PKc");

    EXPECT_TRUE(varPool->exists(varName));
    EXPECT_FALSE(varPool->exists("HandSize"));
}