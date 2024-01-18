# include(FetchContent)
# FetchContent_Declare(
#     rva
#     GIT_REPOSITORY https://github.com/codeinred/recursive-variant.git
#     GIT_TAG        main
# )
# FetchContent_MakeAvailable(rva)

add_library(GameParser GameParser.cpp)
# target_link_libraries(GameParser PRIVATE rva::rva)

target_include_directories(GameParser
PUBLIC
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
$<INSTALL_INTERFACE:include>
)