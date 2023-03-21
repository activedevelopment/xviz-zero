cmake_minimum_required(VERSION 3.25)
project(xviz_zero)

set(CMAKE_CXX_STANDARD 20)

find_package(raylib CONFIG REQUIRED)
find_package(RdKafka REQUIRED)
find_package(nlohmann_json 3.9.1 REQUIRED)

add_executable(xviz_zero main.cpp)

target_link_libraries(xviz_zero PRIVATE raylib RdKafka::rdkafka++ nlohmann_json::nlohmann_json)
