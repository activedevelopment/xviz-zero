cmake_minimum_required(VERSION 3.25)
project(xviz_zero)

set(CMAKE_CXX_STANDARD 20)

#find_package(raylib 4.2.0 REQUIRED)
find_package(raylib CONFIG REQUIRED)

add_executable(xviz_zero main.cpp)

target_link_libraries(xviz_zero PRIVATE raylib)
