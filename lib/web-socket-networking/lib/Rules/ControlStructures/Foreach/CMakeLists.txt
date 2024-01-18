add_library(foreachLib
  Foreach.cpp
)

target_include_directories(foreachLib
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

set_target_properties(foreachLib
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 17
)

target_link_libraries(foreachLib
  rule
  GameConfig
)
