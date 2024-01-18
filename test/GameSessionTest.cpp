#include <assert.h>
#include <iostream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "GameSession.h"
using namespace testing;


class GameSessionTest : public ::testing::Test 
{
 public:
    std::unique_ptr<GameSession> game;

    GameSessionTest()
    {
        game = std::make_unique<GameSession>();
    }
    ~GameSessionTest()
    {
    }
};

// Initialization and check basic states
TEST_F(GameSessionTest, InitDefault) {
    EXPECT_EQ(game->getInviteCode(), 0);
    EXPECT_EQ(game->getPlayers().size(), 0);
    EXPECT_EQ(game->getAudience().size(), 0);
}

// Initialization and check basic states (Non-default Constructor)
TEST_F(GameSessionTest, InitNonDefault) {
    game = std::make_unique<GameSession>(1234);
    EXPECT_EQ(game->getInviteCode(), 1234);
    EXPECT_EQ(game->getPlayers().size(), 0);
    EXPECT_EQ(game->getAudience().size(), 0);
}

// Initialization and check basic states (Non-default Constructor)
TEST_F(GameSessionTest, addPlayer) {
    game = std::make_unique<GameSession>(1234);
    EXPECT_EQ(game->getInviteCode(), 1234);
    EXPECT_EQ(game->getPlayers().size(), 0);
    EXPECT_EQ(game->getAudience().size(), 0);
    game->addPlayer(Users("test"));
    EXPECT_EQ(game->getPlayers().size(), 1);
    EXPECT_EQ(game->getAudience().size(), 0);
}

TEST_F(GameSessionTest, removePlayer) {
    game = std::make_unique<GameSession>(1234);
    EXPECT_EQ(game->getInviteCode(), 1234);
    EXPECT_EQ(game->getPlayers().size(), 0);
    EXPECT_EQ(game->getAudience().size(), 0);
    game->addPlayer(Users("test"));
    EXPECT_EQ(game->getPlayers().size(), 1);
    EXPECT_EQ(game->getAudience().size(), 0);
    game->removePlayer(Users("test"));
    EXPECT_EQ(game->getPlayers().size(), 0);
    EXPECT_EQ(game->getAudience().size(), 0);
}

TEST_F(GameSessionTest, getHost) {
    game = std::make_unique<GameSession>(1234);
    EXPECT_EQ(game->getInviteCode(), 1234);
    EXPECT_EQ(game->getPlayers().size(), 0);
    EXPECT_EQ(game->getAudience().size(), 0);
    game->addPlayer(Users("test"));
    EXPECT_EQ(game->getPlayers().size(), 1);
    EXPECT_EQ(game->getAudience().size(), 0);
}

TEST_F(GameSessionTest, addAudience) {
    game = std::make_unique<GameSession>(1234);
    EXPECT_EQ(game->getInviteCode(), 1234);
    EXPECT_EQ(game->getPlayers().size(), 0);
    EXPECT_EQ(game->getAudience().size(), 0);
    game->addAudience(Users("test"));
    EXPECT_EQ(game->getPlayers().size(), 0);
    EXPECT_EQ(game->getAudience().size(), 1);
}


TEST_F(GameSessionTest, generateCode) {
    game = std::make_unique<GameSession>(1234);
    EXPECT_EQ(game->getInviteCode(), 1234);
    EXPECT_EQ(game->getPlayers().size(), 0);
    EXPECT_EQ(game->getAudience().size(), 0);
    game->generateRandomInviteCode();
    EXPECT_NE(game->getInviteCode(), 1234);
}

TEST_F(GameSessionTest, getPlayers) {
    game = std::make_unique<GameSession>(1234);
    EXPECT_EQ(game->getInviteCode(), 1234);
    EXPECT_EQ(game->getPlayers().size(), 0);
    EXPECT_EQ(game->getAudience().size(), 0);
    game->addPlayer(Users("test"));
    EXPECT_EQ(game->getPlayers() == std::vector<Users>{Users("test")}, true);
}

TEST_F(GameSessionTest, getAudience) {
    game = std::make_unique<GameSession>(1234);
    EXPECT_EQ(game->getInviteCode(), 1234);
    EXPECT_EQ(game->getPlayers().size(), 0);
    EXPECT_EQ(game->getAudience().size(), 0);
    game->addAudience(Users("test"));
    EXPECT_EQ(game->getAudience() == std::vector<Users>{Users("test")}, true);
}

TEST_F(GameSessionTest, getInviteCode) {
    game = std::make_unique<GameSession>(1234);
    EXPECT_EQ(game->getInviteCode(), 1234);
    EXPECT_EQ(game->getPlayers().size(), 0);
    EXPECT_EQ(game->getAudience().size(), 0);
}

// Initialization and check basic states
TEST_F(GameSessionTest, InitDefault) {
    
      ASSERT_EQ( gameSession->GetGameSessionCode(), "");
      ASSERT_EQ( gameSession->GetGameSessionName(), "");

}

// Initialization and check basic states (Changed Identifying Member Variables)
TEST_F(GameSessionTest, InitNonDefault) {
    gameSession->SetGameSessionCode("ACE123");
    gameSession->SetGameSessionName("Test");

    ASSERT_EQ( gameSession->GetGameSessionCode(), "ACE123");
    ASSERT_EQ( gameSession->GetGameSessionName(), "Test");
}

