add_subdirectory(ArithmeticOperations)
add_subdirectory(ControlStructures)
add_subdirectory(HumanInput)
add_subdirectory(ListOperations)
add_subdirectory(Output)
add_subdirectory(Timing)

add_library(rules
  Rules.cpp
)

target_include_directories(rules
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

set_target_properties(rules
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 17
)

target_link_libraries(rules
  rule
)