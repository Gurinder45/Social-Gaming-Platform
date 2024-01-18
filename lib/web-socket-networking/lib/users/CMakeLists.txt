add_library(Users users.cpp)

target_include_directories(Users
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(Users
  networking
  ${CMAKE_THREAD_LIBS_INIT}
)
INSTALL(TARGETS Users
        LIBRARY DESTINATION lib
        PUBLIC_HEADER DESTINATION include
)