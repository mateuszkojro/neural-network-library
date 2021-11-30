cmake_minimum_required(VERSION 3.16)
project(neural_network_c_)

enable_testing()
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(Matrix lib/Matrix/Matrix.h lib/Matrix/Matrix.cc)

include_directories(include)
include_directories(lib/Matrix)

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


add_executable(network src/Network.cpp src/main.cpp)
target_link_libraries(network  ${BLAS_LIBRARIES} ${LAPACK_LIBRARIES})

add_test(NAME Catch2 COMMAND ./tests)