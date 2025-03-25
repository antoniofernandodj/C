cmake_minimum_required(VERSION 3.28)

project(
    CStudy
    VERSION 1.0.0
    LANGUAGES C
)


include_directories("./src")
add_subdirectory(src)
include_directories(
    "${CMAKE_BINARY_DIR}/configured_files/include"
)
add_compile_options(-Wall -Wextra -Werror)
