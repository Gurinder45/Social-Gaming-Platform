#include <assert.h>
#include <iostream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Game.h"
using namespace testing;

class GamesTest : public ::testing::Test 
{
 public:
    std::unique_ptr<Game> game;

    GameTests()
    {
        game = std::make_unique<Game>();
    }

    ~GameTests()
    {
    }
};




