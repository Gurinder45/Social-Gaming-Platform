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
