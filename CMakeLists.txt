cmake_minimum_required(VERSION 3.28)

project(
    CStudy
    VERSION 1.0.0
    LANGUAGES C
)

add_library(Lib STATIC my_lib.c)
add_subdirectory(configured)
add_executable(main main.c)
target_link_libraries(main PUBLIC Lib)
include_directories("${CMAKE_BINARY_DIR}/configured_files/include")
add_compile_options(-Wall -Wextra -Werror)
