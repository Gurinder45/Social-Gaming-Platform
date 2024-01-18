#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <vector>
#include <string>

#include "Deal.h"

class DealTests : public testing::Test
{
public:
private:
};

TEST_F(DealTests, dealIntLists)
{
    std::vector<int> listOne = {1, 2, 3, 4};
    std::vector<int> listTwo = {5, 6, 7, 8};

    Deal deal = Deal(listOne, listTwo, 3);

    deal.execute();

    std::vector<int> expectedResult = {1, 2 ,3 ,4 ,5 ,6 ,7};
    EXPECT_EQ(listOne, expectedResult);
}

TEST_F(DealTests, dealStringLists)
{
    std::vector<std::string> listOne = {"giraffe", "elephant", "monkey"};
    std::vector<std::string> listTwo = {"lion", "zebra", "tiger"};

    Deal deal = Deal(listOne, listTwo, 1);

    deal.execute();

    std::vector<std::string> expectedResult = {"giraffe", "elephant", "monkey", "lion"};
    EXPECT_EQ(listOne, expectedResult);
}

TEST_F(DealTests, dealListOfLists)
{
    std::vector<std::vector<int>> listOne = {{1, 2}, {2, 3}, {3, 4}, {4, 5}};
    std::vector<std::vector<int>> listTwo = {{10, 9}, {8, 9}};

    Deal deal = Deal(listOne, listTwo, 1);

    deal.execute();

    std::vector<std::vector<int>> expectedResult = {{1, 2}, {2, 3}, {3, 4}, {4, 5}, {10, 9}};
    EXPECT_EQ(listOne, expectedResult);
}

TEST_F(DealTests, emptyList)
{
    std::vector<std::string> listOne = {"giraffe", "elephant", "monkey"};
    std::vector<std::string> listTwo = {};

    Deal deal = Deal(listOne, listTwo, 1);

    deal.execute();

    std::vector<std::string> expectedResult = {"giraffe", "elephant", "monkey"};
    EXPECT_EQ(listOne, expectedResult);
}

TEST_F(DealTests, countGreaterThanListSize)
{
    std::vector<std::string> listOne = {"giraffe", "elephant", "monkey"};
    std::vector<std::string> listTwo = {"monkey"};

    Deal deal = Deal(listOne, listTwo, 3);

    deal.execute();

    std::vector<std::string> expectedResult = {"giraffe", "elephant", "monkey", "monkey"};
    EXPECT_EQ(listOne, expectedResult);
}

TEST_F(DealTests, toListEmpty)
{
    std::vector<std::string> listOne = {};
    std::vector<std::string> listTwo = {"monkey"};

    Deal deal = Deal(listOne, listTwo, 1);

    deal.execute();

    std::vector<std::string> expectedResult = {"monkey"};
    EXPECT_EQ(listOne, expectedResult);
}

TEST_F(DealTests, countIsZero)
{
    std::vector<int> listOne = {1};
    std::vector<int> listTwo = {2};

    Deal deal = Deal(listOne, listTwo, 0);

    deal.execute();

    std::vector<int> expectedResult = {1};
    EXPECT_EQ(listOne, expectedResult);
}
