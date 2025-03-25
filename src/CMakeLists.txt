add_library(Lib STATIC my_lib.c)
add_executable(main main.c)
target_link_libraries(main PUBLIC Lib)
target_include_directories(main PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")