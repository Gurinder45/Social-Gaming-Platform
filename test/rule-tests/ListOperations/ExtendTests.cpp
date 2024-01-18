#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <vector>
#include <string>

#include "Extend.h"

class ExtendTests : public testing::Test
{
public:
private:
};

TEST_F(ExtendTests, testIntLists) {
    std::vector<int> listOne = {1, 2, 3};
    std::vector<int> listTwo = {4, 5 ,6};

    Extend extend = Extend(listOne,listTwo);
    extend.execute();

    std::vector<int> expectedResult = {1, 2, 3, 4, 5, 6};
    EXPECT_EQ(listOne, expectedResult);
}

TEST_F(ExtendTests, testStringLists) {
    std::vector<std::string> listOne = {"rock", "paper", "scissors"};
    std::vector<std::string> listTwo = {"lizards", "spock"};

    Extend extend = Extend(listOne,listTwo);
    extend.execute();

    std::vector<std::string> expectedResult = {"rock", "paper", "scissors", "lizards", "spock"};
    EXPECT_EQ(listOne, expectedResult);
}

TEST_F(ExtendTests, testDoubleLists) {
    std::vector<double> listOne = {1.0, 2.4, 3.19};
    std::vector<double> listTwo = {4.1, 5.0 ,6.2};

    Extend extend = Extend(listOne,listTwo);
    extend.execute();

    std::vector<double> expectedResult = {1.0, 2.4, 3.19, 4.1, 5.0 ,6.2};
    EXPECT_EQ(listOne, expectedResult);
}

TEST_F(ExtendTests, testListOfLists) {
    std::vector<std::vector<int>> listOne = {{1, 2, 3}, {1, 2, 3}};
    std::vector<std::vector<int>> listTwo = {{4, 5 ,6}, {4, 5 ,6}};

    Extend extend = Extend(listOne,listTwo);
    extend.execute();

    std::vector<std::vector<int>> expectedResult = {{1, 2, 3}, {1, 2, 3}, {4, 5 ,6}, {4, 5 ,6}};
    EXPECT_EQ(listOne, expectedResult);
}

TEST_F(ExtendTests, testEmptyLists) {
    std::vector<int> listOne = {};
    std::vector<int> listTwo = {};

    Extend extend = Extend(listOne,listTwo);
    extend.execute();

    std::vector<int> expectedResult = {};
    EXPECT_EQ(listOne, expectedResult);
}

TEST_F(ExtendTests, testEmptyFromList) {
    std::vector<int> listOne = {1, 2, 3};
    std::vector<int> listTwo = {};

    Extend extend = Extend(listOne,listTwo);
    extend.execute();

    std::vector<int> expectedResult = {1, 2, 3};
    EXPECT_EQ(listOne, expectedResult);
}
