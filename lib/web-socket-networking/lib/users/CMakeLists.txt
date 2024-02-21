add_library(Users users.cpp)

target_include_directories(Users
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

set_target_properties(Users PROPERTIES PUBLIC_HEADER include/users.h)
INSTALL(TARGETS Users
        LIBRARY DESTINATION lib
        PUBLIC_HEADER DESTINATION include
)