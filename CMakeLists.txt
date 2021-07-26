cmake_minimum_required(VERSION 3.16)
project(neural_network_c_)

set(CMAKE_CXX_STANDARD 14)

add_library(Matrix lib/Matrix/Matrix.h lib/Matrix/Matrix.cc)

include_directories(include)
include_directories(lib/Matrix)

add_executable(
        neural_network_c_
        src/Net.cpp
        src/neural_network_c++.cpp
        )

target_link_libraries(Matrix)