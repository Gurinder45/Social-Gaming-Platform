add_library(GameState GameState.cpp)

target_include_directories(GameState
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fno-rtti -std=c++17 -frtti")

set_target_properties(GameState
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 17
)

INSTALL(TARGETS GameState DESTINATION lib)
INSTALL(FILES include/GameState.h DESTINATION include)
