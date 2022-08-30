cmake_minimum_required(VERSION 3.2)
project(DesignPatternsDemo)

set(CMAKE_CXX_COMPILER)
set(CMAKE_CXX_FLAGS "-Wall")

include_directories(include)
add_executable(${PROJECT_NAME} main.cpp)