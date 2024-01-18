#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <vector>
#include <string>

#include "Reverse.h"

class ReverseTests : public testing::Test
{
public:
private:
};

TEST_F(ReverseTests, testIntList) {
    std::vector<int> list = {1, 2, 3};

    Reverse reverse = Reverse(list);
    reverse.execute();

    std::vector<int> expectedResult = {3, 2, 1};
    EXPECT_EQ(list, expectedResult);
}

TEST_F(ReverseTests, testListOfLists) {
    std::vector<std::vector<int>> list = {{1, 2, 3}, {2, 3, 4}};

    Reverse reverse = Reverse(list);
    reverse.execute();

    std::vector<std::vector<int>> expectedResult = {{2, 3, 4}, {1, 2, 3}};
    EXPECT_EQ(list, expectedResult);
}

TEST_F(ReverseTests, testEmptyList) {
    std::vector<int> list = {};

    Reverse reverse = Reverse(list);
    reverse.execute();

    std::vector<int> expectedResult = {};
    EXPECT_EQ(list, expectedResult);
}
