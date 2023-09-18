cmake_minimum_required(VERSION 3.25)
set(CMAKE_CXX_STANDARD 23)

project(test)

set(PROJECT_HEADERS API/API.h FloodFill/floodfill.h)
set(PROJECT_SOURCES main.cpp API/API.cpp FloodFill/floodfill.cpp)

add_executable(test ${PROJECT_HEADERS} ${PROJECT_SOURCES})
