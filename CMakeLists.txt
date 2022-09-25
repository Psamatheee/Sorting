cmake_minimum_required(VERSION 3.23)
project(Sorting)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
add_executable(Sorting main.cpp)
target_link_libraries(Sorting sfml-graphics sfml-audio)