add_library(RuleParser RuleParser.cpp)


target_include_directories(RuleParser
PUBLIC
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
$<INSTALL_INTERFACE:include>
)


target_link_libraries(RuleParser
    GameConfig
    VarPool
    Rule
)