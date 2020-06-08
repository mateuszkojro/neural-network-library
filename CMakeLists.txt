cmake_minimum_required(VERSION 3.16)
project(neural_network_c_)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(neural_network_c_
        src/array_2d.cpp
        src/matrix.cpp
        src/net.cpp
        src/neural_network_c++.cpp)
