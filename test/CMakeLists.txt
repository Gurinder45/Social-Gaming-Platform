add_subdirectory(gtest)
enable_testing()

add_executable(runAllTests
  Dummy.cpp
  jsonToGame.cpp
  GameConfigTest.cpp
  SetupTest.cpp
  VarPoolTest.cpp
  user_test.cpp
  # You can create new source files for your tests and add them here,
  # or you can add your tests to Dummy.cpp. Either way will work.

  ./rule-tests/ListOperations/DealTests.cpp
  ./rule-tests/ListOperations/DiscardTests.cpp
)

target_link_libraries(runAllTests
  gmock
  gtest
  gtest_main
  GameConfig
  GameSession
  varpool
  Game
  Users

  # Rules Libraries
  deal
  discard
)

add_test(NAME AllTests COMMAND runAllTests)
