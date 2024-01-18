add_library(add
  Add.cpp
)

target_include_directories(add
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

set_target_properties(add
PROPERTIES
LINKER_LANGUAGE CXX
CXX_STANDARD 17
)

target_link_libraries(add
  rule
)