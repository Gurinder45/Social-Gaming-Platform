#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <vector>
#include <string>

#include "Sort.h"

class SortTests : public testing::Test
{
public:
private:
};

TEST_F(SortTests, testIntList)
{
    std::vector<int> list = {3, 2, 1};

    Sort sort = Sort(list, std::greater<int>());
    sort.execute();

    std::vector<int> expectedResult = {1, 2, 3};
    EXPECT_NE(list, expectedResult);
}

TEST_F(SortTests, testListOfLists)
{
    struct
    {
        bool operator()(std::vector<int> &a, std::vector<int> &b) const
        {
            return a[2] < b[2];
        }
    } customSortOperator;

    std::vector<std::vector<int>> list = {{2, 3, 4}, {1, 2, 3}};

    Sort sort = Sort(list, customSortOperator);
    sort.execute();

    std::vector<std::vector<int>> expectedResult = {{1, 2, 3}, {2, 3, 4}};
    EXPECT_EQ(list, expectedResult);
}

TEST_F(SortTests, testEmptyLists)
{
    std::vector<int> list = {};

    Sort sort = Sort(list, std::greater<int>());
    sort.execute();

    std::vector<int> expectedResult = {};
    EXPECT_EQ(list, expectedResult);
}

TEST_F(SortTests, testStringList)
{

    struct
    {
        bool operator()(std::string &s1, std::string &s2)
        {
            std::transform(s1.begin(), s1.end(), s1.begin(),
                           [](char &c)
                           { return std::tolower(c); });
            std::transform(s2.begin(), s2.end(), s2.begin(),
                           [](char &c)
                           { return std::tolower(c); });
            return s1 < s2;
        }
    } customSortOperator;

    std::vector<std::string> simpleList = {"b", "c", "a"};
    Sort simpleSort = Sort(simpleList, customSortOperator);
    simpleSort.execute();

    std::vector<std::string> expectedSimpleResult = {"a", "b", "c"};
    EXPECT_EQ(simpleList, expectedSimpleResult);

    std::vector<std::string> list = {"orange", "strawberry", "apple", "banana"};
    Sort sort = Sort(list, customSortOperator);
    sort.execute();

    std::vector<std::string> expectedResult = {"apple", "banana", "orange", "strawberry"};
    EXPECT_EQ(list, expectedResult);
}
