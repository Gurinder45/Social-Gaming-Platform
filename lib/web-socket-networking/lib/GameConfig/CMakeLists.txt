add_library(GameConfig  GameConfig.cpp)

target_include_directories(GameConfig
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>       
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++17 -frtti")

target_link_libraries(GameConfig
    varpool
    GameSession
)

set_target_properties(GameConfig
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 17
)

INSTALL(TARGETS GameConfig DESTINATION lib)
INSTALL(FILES include/GameConfig.h DESTINATION include)
INSTALL(FILES include/Setup.h DESTINATION include)