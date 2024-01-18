#include <assert.h>
#include <iostream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "users.h"
using namespace testing;

class UsersTests : public ::testing::Test 
{
 public:
    std::unique_ptr<Users> user;

    UsersTests()
    {
        user = std::make_unique<Users>();
    }

    ~UsersTests()
    {
    }
};


// Initialization and check basic states
TEST_F(UsersTests, InitDefault) {

  ASSERT_EQ( user->GetUsername(), "");
  ASSERT_EQ( user->GetUserLevel(), 0);
  ASSERT_EQ( user->GetUserSpectatorStatus(), false);
  ASSERT_EQ( user->GetUserPlayerStatus(), false);
  ASSERT_EQ( user->GetUserHostStatus(), false);
}

// Initialization and check basic states (Non-default Constructor)
TEST_F(UsersTests, InitNonDefault) {
  user->changeUsername("Mike");

  ASSERT_EQ( user->GetUsername(), "Mike");
  ASSERT_EQ( user->GetUserLevel(), 0);
  ASSERT_EQ( user->GetUserSpectatorStatus(), false);
  ASSERT_EQ( user->GetUserPlayerStatus(), false);
  ASSERT_EQ( user->GetUserHostStatus(), false);
}

// Initialization and check basic states (Non-default Constructor)
TEST_F(UsersTests, ChangeUsername) {
  user->changeUsername("Mike");
  ASSERT_EQ( user->GetUsername(), "Mike");

  user->changeUsername("Matt");
  ASSERT_EQ( user->GetUsername(), "Matt");
  ASSERT_EQ( user->GetUserLevel(), 0);
  ASSERT_EQ( user->GetUserSpectatorStatus(), false);
  ASSERT_EQ( user->GetUserPlayerStatus(), false);
  ASSERT_EQ( user->GetUserHostStatus(), false);
}

TEST_F(UsersTests, UserLevelUp) {
  user->UserLevelUp();

  ASSERT_EQ( user->GetUsername(), "");
  ASSERT_EQ( user->GetUserLevel(), 1);
  ASSERT_EQ( user->GetUserSpectatorStatus(), false);
  ASSERT_EQ( user->GetUserPlayerStatus(), false);
  ASSERT_EQ( user->GetUserHostStatus(), false);
}

TEST_F(UsersTests, UserSetHost) {
  user->UserSetHost();

  ASSERT_EQ( user->GetUsername(), "");
  ASSERT_EQ( user->GetUserLevel(), 0);
  ASSERT_EQ( user->GetUserSpectatorStatus(), false);
  ASSERT_EQ( user->GetUserPlayerStatus(), false);
  ASSERT_EQ( user->GetUserHostStatus(), true);
}

TEST_F(UsersTests, UserSetSpectator) {
  user->UserSetSpectator();

  ASSERT_EQ( user->GetUsername(), "");
  ASSERT_EQ( user->GetUserLevel(), 0);
  ASSERT_EQ( user->GetUserSpectatorStatus(), true);
  ASSERT_EQ( user->GetUserPlayerStatus(), false);
  ASSERT_EQ( user->GetUserHostStatus(), false);
}


TEST_F(UsersTests, UserSetPlayer) {
  user->UserSetPlayer();

  ASSERT_EQ( user->GetUsername(), "");
  ASSERT_EQ( user->GetUserLevel(), 0);
  ASSERT_EQ( user->GetUserSpectatorStatus(), false);
  ASSERT_EQ( user->GetUserPlayerStatus(), true);
  ASSERT_EQ( user->GetUserHostStatus(), false);
}

TEST_F(UsersTests, UserSetHostThenPlayer) {
  user->UserSetHost();
  user->UserSetPlayer();

  ASSERT_EQ( user->GetUsername(), "");
  ASSERT_EQ( user->GetUserLevel(), 0);
  ASSERT_EQ( user->GetUserSpectatorStatus(), false);
  ASSERT_EQ( user->GetUserPlayerStatus(), true);
  ASSERT_EQ( user->GetUserHostStatus(), true);
}

TEST_F(UsersTests, UserRemoveSpectator) {
  user->UserSetSpectator();
   ASSERT_EQ( user->GetUserSpectatorStatus(), true);

  user->UserRemoveSpectator();
  ASSERT_EQ( user->GetUsername(), "");
  ASSERT_EQ( user->GetUserLevel(), 0);
  ASSERT_EQ( user->GetUserSpectatorStatus(), false);
  ASSERT_EQ( user->GetUserPlayerStatus(), false);
  ASSERT_EQ( user->GetUserHostStatus(), false);
}

TEST_F(UsersTests, UserRemoveHost) {
  user->UserSetHost();
  ASSERT_EQ( user->GetUserHostStatus(), true);

  user->UserRemoveHost();
  ASSERT_EQ( user->GetUsername(), "");
  ASSERT_EQ( user->GetUserLevel(), 0);
  ASSERT_EQ( user->GetUserSpectatorStatus(), false);
  ASSERT_EQ( user->GetUserPlayerStatus(), false);
  ASSERT_EQ( user->GetUserHostStatus(), false);
}


