add_library(inputChoice
  InputChoice.cpp
)

target_include_directories(inputChoice
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

set_target_properties(inputChoice
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 17
)

target_link_libraries(inputChoice
  rule
  basicInput
)
