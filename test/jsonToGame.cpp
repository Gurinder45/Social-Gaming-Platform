#include "Game.h"
#include "GameConfig.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

class jsonToGameTest : public ::testing::Test{
protected:
    std::unique_ptr<Game> game;
    GameConfig* config;
    void SetUp() override{
        game = std::make_unique<Game>();
        config = game->getGameConfig();
    }
    // void TearDown() override{
    //     game->~Game();
    // }
};

// TEST_F (jsonToGameTest, initialize){
//     EXPECT_EQ(config->getName(), "");
//     EXPECT_EQ(config->audienceAllowed(),false);
//     EXPECT_EQ(config->getMinPlayerCount(), 0);
//     EXPECT_EQ(config->getMaxPlayerCount(), 0);
// }

// TEST_F (jsonToGameTest, readJson){
//     EXPECT_EQ(game->getConfigFromFile("../test/Nofile.json"), "Failure");

// }

// TEST_F (jsonToGameTest, differentGame){
//     EXPECT_EQ(game->getConfigFromFile("../test/testGame.json"), "Success");
//     EXPECT_EQ(config->getName(), "test Game");
//     EXPECT_EQ(config->audienceAllowed(),true);
//     EXPECT_EQ(config->getMinPlayerCount(), 50);
//     EXPECT_EQ(config->getMaxPlayerCount(), 100);
// }