cmake_minimum_required(VERSION 3.25)

project(cj2engine VERSION 0.1.0)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(libs)
add_subdirectory(framework)
add_subdirectory(platforms)
add_subdirectory(tiny-renderer)

add_subdirectory(demos)
