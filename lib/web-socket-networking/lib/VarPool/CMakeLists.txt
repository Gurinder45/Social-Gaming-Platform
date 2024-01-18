add_library(varpool
  VarPool.cpp
)
target_include_directories(varpool
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++17 -frtti")

set_target_properties(varpool
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 17
)

INSTALL(TARGETS varpool DESTINATION lib)
INSTALL(FILES include/VarPool.h DESTINATION include)
