cmake_minimum_required(VERSION 3.16)
project(ish VERSION 0.1 LANGUAGES C)
set(CMAKE_C_COMPILER gcc)

add_executable(main src/main.c)
target_link_libraries(main readline)
