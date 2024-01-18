add_library(rule
  Rule.cpp
)




target_include_directories(rule
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)



set_target_properties(rule
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 17
)

target_link_libraries(rule GameConfig)
target_link_libraries(rule add)
target_link_libraries(rule foreachLib)
target_link_libraries(rule rules)
target_link_libraries(rule timer)
target_link_libraries(rule inputChoice)
target_link_libraries(rule inputText)
target_link_libraries(rule inputVote)
target_link_libraries(rule globalMessage)
target_link_libraries(rule message)
target_link_libraries(rule scores)
target_link_libraries(rule loop)
target_link_libraries(rule inParallel)
target_link_libraries(rule parallelFor)
target_link_libraries(rule switch)
target_link_libraries(rule when)
target_link_libraries(rule condition)
target_link_libraries(rule extend)
target_link_libraries(rule reverse)
target_link_libraries(rule shuffle)
target_link_libraries(rule sort)
target_link_libraries(rule deal)
target_link_libraries(rule discard)
target_link_libraries(rule GameSession)