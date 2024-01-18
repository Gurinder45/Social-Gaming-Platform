#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <vector>
#include <string>

#include "Deal.h"
#include "Shuffle.h"
#include "users.h"
#include "Shuffle.h"

class ShuffleTests : public testing::Test
{
public:
private:
};

//Since the whole point of shuffle is to make things random, it's a little hard to make sure it worked correctly
//The best thing to do might be to shuffle, then sort and make sure none of the items got lost/deleted
TEST_F(ShuffleTests, shuffleIntLists)
{
    std::vector<int> listOne = {1, 2, 3, 4};
 
    Shuffle shuffle = Shuffle(listOne);

    shuffle.execute();

    std::sort(listOne.begin(), listOne.end());

    std::vector<int> expected = {1, 2 ,3, 4};


    
    EXPECT_TRUE(listOne==expected);
}

TEST_F(ShuffleTests, shuffleChars)
{
    std::vector<char> listOne = {'a', 'b', 'c', 'd'};
 
    Shuffle shuffle = Shuffle(listOne);

    shuffle.execute();

    std::sort(listOne.begin(), listOne.end());

    std::vector<char> expected = {'a', 'b', 'c', 'd'};
    EXPECT_TRUE(listOne == expected);
}


TEST_F(ShuffleTests, shuffleStrings)
{
    std::vector<std::string> listOne = {"aa", "bb", "cc", "dd"};
 
    Shuffle shuffle = Shuffle(listOne);

    shuffle.execute();

    std::sort(listOne.begin(), listOne.end());

    std::vector<std::string> expected = {"aa", "bb", "cc", "dd"};
    EXPECT_TRUE(listOne == expected);
}

// TEST_F(ShuffleTests, shuffleUsers)
// {

//     Users user1 = Users("user1");
//     Users user2 = Users("user2");
//     Users user3 = Users("user3");
//     Users user4 = Users("user4");
//     Users user5 = Users("user5");

//     std::vector<Users> usersList = {user1, user2, user3, user4, user5};

//     Shuffle shuffle = Shuffle(usersList);

//     shuffle.execute();

//     std::sort(usersList.begin(), usersList.end());

//     std::vector<Users> expected = {user1, user2, user3, user4, user5};
//     EXPECT_TRUE(usersList == expected);
// }



TEST_F(ShuffleTests, testIntList) {
    std::vector<int> list = {1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3};

    Shuffle shuffle = Shuffle(list);
    shuffle.execute();

    std::vector<int> expectedResult = {1, 2, 3};
    EXPECT_NE(list, expectedResult);
}

TEST_F(ShuffleTests, testListOfLists) {
    std::vector<std::vector<int>> list = {{1, 2, 3}, {2, 3, 4}, {1}, {2}, {6, 3}, {1, 4}};

    Shuffle shuffle = Shuffle(list);
    shuffle.execute();

    std::vector<std::vector<int>> expectedResult = {{1, 2, 3}, {2, 3, 4}, {1}, {2}, {6, 3}, {1, 4}};
    EXPECT_NE(list, expectedResult);
}

TEST_F(ShuffleTests, testEmptyLists) {
    std::vector<int> list = {};

    Shuffle shuffle = Shuffle(list);
    shuffle.execute();

    std::vector<int> expectedResult = {};
    EXPECT_EQ(list, expectedResult);
}
