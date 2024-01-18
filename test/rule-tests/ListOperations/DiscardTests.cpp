#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <vector>
#include <string>

#include "Discard.h"

class DiscardTests : public testing::Test
{
public:
private:
};

TEST_F(DiscardTests, discardIntLists)
{
    std::vector<int> list = {1, 2, 3, 4};

    Discard discard = Discard(list, 3);

    discard.execute();

    std::vector<int> expectedResult = {1};
    EXPECT_EQ(list, expectedResult);
}

TEST_F(DiscardTests, discardStringLists)
{
    std::vector<std::string> list = {"one", "two", "three"};

    Discard discard = Discard(list, 1);

    discard.execute();

    std::vector<std::string> expectedResult = {"one", "two"};
    EXPECT_EQ(list, expectedResult);
}

TEST_F(DiscardTests, discardListOfLists)
{
    std::vector<std::vector<int>> list = {{1, 2}, {2, 3}, {3, 4}, {4, 5}};

    Discard discard = Discard(list, 2);

    discard.execute();

    std::vector<std::vector<int>> expectedResult = {{1, 2}, {2, 3}};
    EXPECT_EQ(list, expectedResult);
}

TEST_F(DiscardTests, emptyList)
{
    std::vector<std::string> list = {};

    Discard discard = Discard(list, 1);

    discard.execute();

    std::vector<std::string> expectedResult = {};
    EXPECT_EQ(list, expectedResult);
}

TEST_F(DiscardTests, countGreaterThanListSize)
{
    std::vector<std::string> list = {"one", "two", "three"};

    Discard discard = Discard(list, 4);

    discard.execute();

    std::vector<std::string> expectedResult = {};
    EXPECT_EQ(list, expectedResult);
}

TEST_F(DiscardTests, countIsZero)
{
    std::vector<int> list = {1};

    Discard discard = Discard(list, 0);

    discard.execute();

    std::vector<int> expectedResult = {1};
    EXPECT_EQ(list, expectedResult);
}
