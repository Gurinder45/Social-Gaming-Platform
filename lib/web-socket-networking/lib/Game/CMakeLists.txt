add_library(Game Game.cpp)

target_include_directories(Game
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(Game
    GameSession
    GameConfig
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fno-rtti -std=c++17 -frtti")

set_target_properties(Game
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 17
)

INSTALL(TARGETS Game DESTINATION lib)
INSTALL(FILES include/Game.h DESTINATION include)


target_link_libraries(Game rule)