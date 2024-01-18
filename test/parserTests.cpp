#include "../lib/web-socket-networking/lib/networking/include/CommandHandler.h"
#include "../lib/web-socket-networking/lib/networking/include/Parser.h"
// Test Headers
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <glog/logging.h>

class parserTests : public ::testing::Test
{
protected:
    Parser p;

    void SetUp() override
    {
        p = Parser();
    }
};

TEST_F(parserTests, validGameFileTest)
{
    std::string expectedGameFile = "{\"configuration\":{\"audience\":false,\"name\":\"Zen Game\",\"player count\":{\"max\":0,\"min\":0},\"setup\":{}},\"constants\":{},\"per-audience\":{},\"per-player\":{},\"rules\":{},\"variables\":{}}";

    std::string parsedResult = p.parseFile("testGameFiles/gamefile.json");

    EXPECT_EQ(expectedGameFile, parsedResult);
}

TEST_F(parserTests, invalidGameFileTests)
{
    std::string expectedResult = "Invalid json file";

    std::string parsedResult = p.parseFile("testGameFiles/invalidGameFile.json");

    EXPECT_EQ(expectedResult, parsedResult);

    parsedResult = p.parseFile("testGameFiles/emptyGameFile.json");

    EXPECT_EQ(expectedResult, parsedResult);
}


TEST_F(parserTests, fileToJsonObjTest)
{
    //not sure how to actually test the fileToJsonObj functions
}

