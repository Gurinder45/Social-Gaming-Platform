add_subdirectory(gtest)
enable_testing()

add_executable(runAllTests
  Dummy.cpp
  jsonToGame.cpp
  GameConfigTest.cpp
  SetupTest.cpp
  VarPoolTest.cpp
  user_test.cpp
  RuleParserTest.cpp
  GameParserTest.cpp
  GameSessionTest.cpp
  parserTests.cpp
  commandHandlerTests.cpp

  # You can create new source files for your tests and add them here,
  # or you can add your tests to Dummy.cpp. Either way will work.

  # Rules Tests
  ./rule-tests/ListOperations/DealTests.cpp
  ./rule-tests/ListOperations/DiscardTests.cpp
  ./rule-tests/ListOperations/ExtendTests.cpp
  ./rule-tests/ListOperations/ReverseTests.cpp
  ./rule-tests/ListOperations/ShuffleTests.cpp
  ./rule-tests/ListOperations/SortTests.cpp
)

target_link_libraries(runAllTests
  gmock
  gtest
  gtest_main
  GameConfig
  GameSession
  GameParser
  varpool
  Game
  Users
  RuleParser

  # Rules Libraries
  deal
  discard
  shuffle
  sort
  extend
  reverse
  shuffle
  sort

)

add_test(NAME AllTests COMMAND runAllTests)
