cmake_minimum_required(VERSION 3.0.0)
project(c++_try VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)

add_executable(titanic src/main.cpp src/titanic.h src/titanic.cpp)

