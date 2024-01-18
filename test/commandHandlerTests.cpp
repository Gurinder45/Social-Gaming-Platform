#include "../lib/web-socket-networking/lib/networking/include/CommandHandler.h"
// Test Headers
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <glog/logging.h>

class commandHandlerTest : public ::testing::Test
{
protected:
    CommandHandler ch;

    void SetUp() override
    {
        ch = CommandHandler();
    }
};

TEST_F(commandHandlerTest, stringToCommandTest)
{

    Command command = ch.stringToCommandEnum("/addgame");
    EXPECT_EQ(command, Command::ADDGAME);

    command = ch.stringToCommandEnum("/disconnect");
    EXPECT_EQ(command, Command::DISCONNECT);

    command = ch.stringToCommandEnum("/joingame");
    EXPECT_EQ(command, Command::JOIN_GAME);

    command = ch.stringToCommandEnum("/creategame");
    EXPECT_EQ(command, Command::CREATE_GAME);

    command = ch.stringToCommandEnum("/changeusername");
    EXPECT_EQ(command, Command::CHANGE_USERNAME);

    command = ch.stringToCommandEnum("/leavegame");
    EXPECT_EQ(command, Command::LEAVE_GAME);

    command = ch.stringToCommandEnum("/gameID");
    EXPECT_EQ(command, Command::GAME_ID);
}

TEST_F(commandHandlerTest, invalidCommands)
{

    Command command = ch.stringToCommandEnum("/badCommand");
    EXPECT_EQ(command, Command::INVALID);

    command = ch.stringToCommandEnum("/");
    EXPECT_EQ(command, Command::INVALID);

    command = ch.stringToCommandEnum("");
    EXPECT_EQ(command, Command::INVALID);
}

TEST_F(commandHandlerTest, saveGameFileNameTest)
{
    std::string gameFileName = "gameFile";
    // std::string saveGameFileName = ch.formatSaveGameFileName(gameFileName);

    // EXPECT_EQ(saveGameFileName, "savedGames/gameFile.json");
}

TEST_F(commandHandlerTest, processInputTest)
{

    CommandAndArguments comAndArgs;
    std::string changeUserNameCommand = "/changeusername newName";
    std::string addGameCommand = "/addgame {\"name\":\"John\", \"age\":30, \"car\":null}";
    std::string genericCommand = "/command arg1 arg2";
    std::string commandWithNoArgs = "/disconnect";

    comAndArgs = ch.processInput(changeUserNameCommand);

    EXPECT_EQ(comAndArgs.command, "/changeusername");
    EXPECT_EQ(comAndArgs.arguments, std::vector<std::string>{"newName"});
    EXPECT_EQ(comAndArgs.allArguments, "newName");

    comAndArgs = ch.processInput(addGameCommand);

    std::vector<std::string> separatedStrings = {"{\"name\":\"John\",", "\"age\":30,", "\"car\":null}"};

    EXPECT_EQ(comAndArgs.command, "/addgame");
    EXPECT_EQ(comAndArgs.arguments, separatedStrings);
    EXPECT_EQ(comAndArgs.allArguments, "{\"name\":\"John\", \"age\":30, \"car\":null}");

    separatedStrings = {"arg1", "arg2"};

    comAndArgs = ch.processInput(genericCommand);
    EXPECT_EQ(comAndArgs.command, "/command");
    EXPECT_EQ(comAndArgs.arguments, separatedStrings);
    EXPECT_EQ(comAndArgs.allArguments, "arg1 arg2");

    comAndArgs = ch.processInput(commandWithNoArgs);
    EXPECT_EQ(comAndArgs.command, "/disconnect");
    EXPECT_EQ(comAndArgs.arguments, std::vector<std::string>{});
    EXPECT_EQ(comAndArgs.allArguments, "");
}