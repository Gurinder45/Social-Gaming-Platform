
add_executable(chatserver
  chatserver.cpp
)

set_target_properties(chatserver
                      PROPERTIES
                      LINKER_LANGUAGE CXX
                      CXX_STANDARD 17
                      PREFIX ""
)

find_package(Threads REQUIRED)

target_link_libraries(chatserver
  networking
  ${CMAKE_THREAD_LIBS_INIT}
)

target_link_libraries(chatserver Game)
target_link_libraries(chatserver GameConfig)
target_link_libraries(chatserver Users)
target_link_libraries(chatserver GameSession)

install(TARGETS chatserver
  RUNTIME DESTINATION bin
)

