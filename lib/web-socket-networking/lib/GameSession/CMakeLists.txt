add_library(GameSession GameSession.cpp)

target_include_directories(GameSession
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(GameSession
    Game
    GameConfig
    Users
)