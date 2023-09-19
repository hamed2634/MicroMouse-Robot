cmake_minimum_required(VERSION 3.25)
set(CMAKE_CXX_STANDARD 23)

project(Project)

set(PROJECT_HEADERS API/API.h floodfill/floodfill.h)
set(PROJECT_SOURCES API/API.cpp floodfill/floodfill.cpp main.cpp)

add_executable(Project ${PROJECT_HEADERS} ${PROJECT_SOURCES})
