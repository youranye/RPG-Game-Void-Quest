cmake_minimum_required(VERSION 3.20)
project(VoidQuest)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

include_directories(include)

add_subdirectory(src)
add_subdirectory(test)