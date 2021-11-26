cmake_minimum_required(VERSION 3.16)
project(neural_network_c_)

enable_testing()
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(Matrix lib/Matrix/Matrix.h lib/Matrix/Matrix.cc)

include_directories(include)
include_directories(lib/Matrix)

add_executable(
        neural_network_c_
        src/Net.cpp
        src/neural_network_c++.cpp
        include/Network.h src/Network.cpp)

target_link_libraries(neural_network_c_ Matrix)

add_subdirectory(lib/Catch2)
include_directories(lib/Catch2/single_include)
add_executable(tests tests/TestsMain.cc tests/TestMatrix.cc)
target_link_libraries(tests PRIVATE
        Matrix
        Catch2::Catch2
        )



add_subdirectory(lib/eigen)
include_directories(lib/eigen/)
include_directories(lib/sciplot/)
#add_subdirectory(lib/xtensor-blas)
#include_directories(lib/xtensor-blas/include)
#add_subdirectory(lib/xtensor)
#include_directories(lib/xtensor/include)
#add_subdirectory(lib/xtl)
#include_directories(lib/xtl/include)
#
#find_package(xtensor REQUIRED CONFIG)
#find_package(xtensor REQUIRED CONFIG)
#find_package(xtensor-blas)

#set(requiredlibs "lapack")
#list(APPEND requiredlibs "stdc++")
#list(APPEND requiredlibs "lapack")


add_executable(network src/Network.cpp src/main.cpp)
target_link_libraries(network  ${BLAS_LIBRARIES} ${LAPACK_LIBRARIES})

add_test(NAME Catch2 COMMAND ./tests)