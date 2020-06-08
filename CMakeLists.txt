cmake_minimum_required(VERSION 3.16)
project(neural_network_c_)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(neural_network_c_
        array_2d.cpp
        array_2d.h
        matrix.cpp
        matrix.h
        net.cpp
        net.h
        neural_network_c++.cpp)
