cmake_minimum_required(VERSION 3.28)
project(coroutines)

set(LIB_TARGET ${PROJECT_NAME})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(third_party)
add_subdirectory(${LIB_TARGET})
add_subdirectory(play)
