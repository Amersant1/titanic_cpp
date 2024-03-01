cmake_minimum_required(VERSION 3.0.0)
project(c++_try VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_PREFIX_PATH "../or-tools/share/eigen3/cmake")
find_package(Eigen3 3.1.0 REQUIRED NO_MODULE)
set(CMAKE_PREFIX_PATH "../or-tools/lib/cmake")
find_package(ortools CONFIG REQUIRED)

add_executable(c++_try src/main.cpp src/titanic.h src/titanic.cpp
        src/ortool.h)
target_link_libraries(c++_try ortools::ortools)
